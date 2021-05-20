from smbus import SMBus
import time

SHT20_I2C              = 0x40
SHT20_TEMP_HM          = 0xE3
SHT20_HUMID_HM         = 0xE5
SHT20_WRITE_USER_REG   = 0xE6
SHT20_READ_USER_REG    = 0xE7
SHT20_RESET            = 0xFE
_DISABLE_ONCHIP_HEATER = 0b00000000
_ENABLE_OTP_RELOAD     = 0b00000000
_DISABLE_OTP_RELOAD    = 0b00000010
_RESERVED_BITMASK      = 0b00111000

class SHT20():
    SOFT_RESET_DELAY   = 0.02
    TEMPERATURE_DELAY  = 0.1
    HUMIDITY_DELAY     = 0.04
    RESOLUTION_12BITS  = 0b00000000
    RESOLUTION_11BITS  = 0b10000001
    RESOLUTION_10BITS  = 0b10000000
    RESOLUTION_8BITS   = 0b00000001

    def __init__(self, bus=3, resolution=RESOLUTION_12BITS):
        self.bus = SMBus(bus)

        self._resolution = resolution
        self._onchip_heater = _DISABLE_ONCHIP_HEATER
        self._otp_reload = _DISABLE_OTP_RELOAD

        self.bus.write_byte(SHT20_I2C, SHT20_RESET)
        time.sleep(self.SOFT_RESET_DELAY)

        config = self.bus.read_byte_data(SHT20_I2C, SHT20_READ_USER_REG)
        config = ((config & _RESERVED_BITMASK) | self._resolution | self._onchip_heater | self._otp_reload)
        #self.bus.write_byte(SHT20_I2C, SHT20_WRITE_USER_REG)
        self.bus.write_byte_data(SHT20_I2C, SHT20_WRITE_USER_REG, config)

    def humidity(self):
        self.bus.write_byte(SHT20_I2C, SHT20_HUMID_HM)
        time.sleep(self.HUMIDITY_DELAY)
        msb, lsb, crc = self.bus.read_i2c_block_data(SHT20_I2C, SHT20_HUMID_HM, 3)
        return -6.0 + 125.0 * (msb * 256.0 + lsb) / 65536.0

    def temperature(self):
        self.bus.write_byte(SHT20_I2C, SHT20_TEMP_HM)
        time.sleep(self.TEMPERATURE_DELAY)
        msb, lsb, crc = self.bus.read_i2c_block_data(SHT20_I2C, SHT20_TEMP_HM, 3)
        return -46.85 + 175.72 * (msb * 256.0 + lsb) / 65536

    def temperature_f(self):
        return (self.temperature * 1.8 + 32)

    def connected(self):
        retval = self.bus.read_byte_data(SHT20_I2C, SHT20_READ_USER_REG)
        if retval != 0xFF:
            return True
        else:
            return False


