#include "i2c_master.h"
#include "pointing_device.h"
#include "navigator_trackball.h"
#include <stdint.h>
#include <stdio.h>
#include "quantum.h"

const pointing_device_driver_t navigator_trackball_pointing_device_driver = {
    .init       = navigator_trackball_device_init,
    .get_report = navigator_trackball_get_report,
    .get_cpi    = navigator_trackball_get_cpi,
    .set_cpi    = navigator_trackball_set_cpi
};

uint8_t current_cpi = DEFAULT_CPI_TICK;

uint8_t has_motion = 0;

uint8_t trackball_init = 0;

deferred_token callback_token = 0;

paw3805ek_reg_seq_t paw3805ek_configure_seq[] = {
    {0x06, 0x80},                 // Software reset
    {0x00, 0x00},                 // Request the sensor ID
    {0x09 | WRITE_REG_BIT, 0x5A}, // Disable the write protection
#ifdef MOUSE_EXTENDED_REPORT
    {0x19 | WRITE_REG_BIT, 0x30}, // Set the sensor orientation, set motion data length to 16 bits
#else
    {0x19 | WRITE_REG_BIT, 0x34}, // Set the sensor orientation, set motion data length to 8 bits
#endif
    //{0x26 | WRITE_REG_BIT, 0x10}, // Enable burst mode
    {0x09 | WRITE_REG_BIT, 0x00}, // Enable the write protection
};

i2c_status_t sci18is606_write(uint8_t *data, uint8_t length) {
    return i2c_transmit(NAVIGATOR_TRACKBALL_ADDRESS, data, length, NAVIGATOR_TRACKBALL_TIMEOUT);
}

i2c_status_t sci18is606_read(uint8_t *data, uint8_t length) {
    return i2c_receive(NAVIGATOR_TRACKBALL_ADDRESS, data, length, NAVIGATOR_TRACKBALL_TIMEOUT);
}

i2c_status_t sci18is606_spi_tx(uint8_t *data, uint8_t length, bool read) {
    i2c_status_t status = sci18is606_write(data, length);
    wait_us(length * 15);
    // Read the SPI response if the command expects it
    if (read) {
        status = sci18is606_read(data, length);
    }
    if (status != I2C_STATUS_SUCCESS) {
        trackball_init = 0;
    }
    return status;
}

i2c_status_t sci18is606_configure(void) {
    uint8_t      spi_conf[2] = {SCI18IS606_CONF_SPI, SCI18IS606_CONF};
    i2c_status_t status      = sci18is606_write(spi_conf, 2);
    wait_ms(10);
    if (status != I2C_STATUS_SUCCESS) {
        trackball_init = 0;
    }
    return status;
}

bool paw3805ek_set_cpi(void) {
    uint8_t next_cpi_x = 0;
    uint8_t next_cpi_y = 0;
    // traverse the sequence by compairing the cpi_x value with the current cpi_x value
    // set the cpi to the next value in the sequence
    switch (current_cpi) {
        case 1: {
            next_cpi_x = CPI_X_800;
            next_cpi_y = CPI_Y_800;
            break;
        }
        case 2: {
            next_cpi_x = CPI_X_1000;
            next_cpi_y = CPI_Y_1000;
            break;
        }
        case 3: {
            next_cpi_x = CPI_X_1200;
            next_cpi_y = CPI_Y_1200;
            break;
        }
        case 4: {
            next_cpi_x = CPI_X_1600;
            next_cpi_y = CPI_Y_1600;
            break;
        }
        case 5: {
            next_cpi_x = CPI_X_2000;
            next_cpi_y = CPI_Y_2000;
            break;
        }
        case 6: {
            next_cpi_x = CPI_X_2400;
            next_cpi_y = CPI_Y_2400;
            break;
        }
        case 7: {
            next_cpi_x = CPI_X_3000;
            next_cpi_y = CPI_Y_3000;
            break;
        }
        default: {
            current_cpi = DEFAULT_CPI_TICK;
            next_cpi_x  = CPI_X_800;
            next_cpi_y  = CPI_Y_800;
            break;
        }
    }

    paw3805ek_reg_seq_t cpi_reg_seq[] = {
        {0x09 | WRITE_REG_BIT, 0x5A}, // Disable write protection
        {0x0D | WRITE_REG_BIT, next_cpi_x},
        {0x0E | WRITE_REG_BIT, next_cpi_y},
        {0x09 | WRITE_REG_BIT, 0x00}, // Enable the write protection
    };

    for (uint8_t i = 0; i < sizeof(cpi_reg_seq) / sizeof(paw3805ek_reg_seq_t); i++) {
        uint8_t buf[3];
        buf[0] = NCS_PIN;
        buf[1] = cpi_reg_seq[i].reg;
        buf[2] = cpi_reg_seq[i].data;
        if (sci18is606_spi_tx(buf, 3, true) != I2C_STATUS_SUCCESS) {
            return false;
        }
    }

    return true;
}

bool paw3805ek_configure(void) {
    for (uint8_t i = 0; i < sizeof(paw3805ek_configure_seq) / sizeof(paw3805ek_reg_seq_t); i++) {
        uint8_t buf[3];
        buf[0] = NCS_PIN;
        buf[1] = paw3805ek_configure_seq[i].reg;
        buf[2] = paw3805ek_configure_seq[i].data;
        if (sci18is606_spi_tx(buf, 3, true) != I2C_STATUS_SUCCESS) {
            return false;
        }
        // Wait for the sensor to restart after the software reset cmd
        wait_ms(1);

        // Check the sensor ID to validate the spi link after the reset
        if (i == 1 && buf[1] != PAW3805EK_ID) {
            return false;
        }
    }

    return true;
}

bool paw3805ek_has_motion(void) {
    uint8_t motion[3] = {0x01, 0x02, 0x00};
    if (sci18is606_spi_tx(motion, 3, true) != I2C_STATUS_SUCCESS) {
        return false;
    }
    return motion[1] & 0x80;
}

void paw3804ek_read_motion(report_mouse_t *mouse_report) {
#ifdef MOUSE_EXTENDED_REPORT
    uint8_t delta_x_l[2] = {0x01, 0x03};
    if (sci18is606_spi_tx(delta_x_l, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    uint8_t delta_y_l[2] = {0x01, 0x04};
    if (sci18is606_spi_tx(delta_y_l, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    uint8_t delta_x_h[2] = {0x01, 0x11};
    if (sci18is606_spi_tx(delta_x_h, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    uint8_t delta_y_h[2] = {0x01, 0x12};
    if (sci18is606_spi_tx(delta_y_h, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    mouse_report->x = (int16_t)((delta_x_h[1] << 8) | delta_x_l[1]);
    mouse_report->y = (int16_t)((delta_y_h[1] << 8) | delta_y_l[1]);
#else
    uint8_t delta_x[2] = {0x01, 0x03};
    if (sci18is606_spi_tx(delta_x, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    uint8_t delta_y[2] = {0x01, 0x04};
    if (sci18is606_spi_tx(delta_y, 3, true) != I2C_STATUS_SUCCESS) {
        return;
    }

    mouse_report->x = delta_x[1];
    mouse_report->y = delta_y[1];
#endif
}

uint32_t sci18is606_read_callback(uint32_t trigger_time, void *cb_arg) {
    if (!trackball_init) {
        navigator_trackball_device_init();
        return NAVIGATOR_TRACKBALL_PROBE;
    }
    if (paw3805ek_has_motion()) {
        has_motion = 1;
    }
    return NAVIGATOR_TRACKBALL_READ;
}

void navigator_trackball_device_init(void) {
    i2c_init();
    if (sci18is606_configure() == I2C_STATUS_SUCCESS) {
        paw3805ek_configure();
    } else {
        return;
    }

    trackball_init = 1;
    if (!callback_token) {
        // Register the callback to read the trackball motion
        callback_token = defer_exec(NAVIGATOR_TRACKBALL_READ, sci18is606_read_callback, NULL);
    }
}

report_mouse_t navigator_trackball_get_report(report_mouse_t mouse_report) {
    if (!trackball_init) {
        return mouse_report;
    }

    if (has_motion) {
        has_motion = 0;
        paw3804ek_read_motion(&mouse_report);
    }
    return mouse_report;
}

uint16_t navigator_trackball_get_cpi(void) {
    return current_cpi;
}

void restore_cpi(uint8_t cpi) {
    current_cpi = cpi;
    paw3805ek_set_cpi();
}

void navigator_trackball_set_cpi(uint16_t cpi) {
    if (cpi == 0) { // Decrease one tick
        if (current_cpi > 1) {
            current_cpi--;
            paw3805ek_set_cpi();
        }
    } else {
        if (current_cpi < CPI_TICKS) {
            current_cpi++;
            paw3805ek_set_cpi();
        }
    }
};
