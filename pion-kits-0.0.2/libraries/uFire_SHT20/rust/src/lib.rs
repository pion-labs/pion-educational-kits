//! # uFire SHT20 library
//!
//! * measure temperature
//! * measure humidity

use std::f32;
use std::thread;
use std::time::Duration;
use std::mem;

extern crate byteorder;
use byteorder::{ByteOrder, LittleEndian};

extern crate i2cdev;
use self::i2cdev::core::*;
use self::i2cdev::linux::{LinuxI2CDevice, LinuxI2CError};

const SHT20_I2C: u16 =              0x40;
const SHT20_TEMP_HM: u8 =           0xE3;
const SHT20_HUMID_HM : u8 =         0xE5;
const SHT20_WRITE_USER_REG: u8 =    0xE6;
const SHT20_READ_USER_REG: u8 =     0xE7;
const SHT20_RESET: u8 =             0xFE;
const _DISABLE_ONCHIP_HEATER: u8 =  0b00000000;
const _ENABLE_OTP_RELOAD: u8 =      0b00000000;
const _DISABLE_OTP_RELOAD: u8 =     0b00000010;
const _RESERVED_BITMASK: u8 =       0b00111000;
const SOFT_RESET_DELAY: u64 =       20;
const TEMPERATURE_DELAY: u64 =      100;
const HUMIDITY_DELAY: u64 =         40;
pub const RESOLUTION_12BITS: u8 =   0b00000000;
pub const RESOLUTION_11BITS: u8 =   0b10000001;
pub const RESOLUTION_10BITS: u8 =   0b10000000;
pub const RESOLUTION_8BITS: u8 =    0b00000001;

pub struct SHT20 {
    dev: Box<LinuxI2CDevice>,
}

impl SHT20 {
    /// Create a new SHT20 object
    ///
    /// Pass the i2c port to use.
    /// # Example
    /// ```
    /// let mut sht20 = SHT20::new("/dev/i2c-3").unwrap();
    /// ```
    pub fn new(filename: &'static str) -> Result<Self, Box<LinuxI2CError>> {
        let dev = LinuxI2CDevice::new(filename, SHT20_I2C)?;

        Ok(SHT20 { dev: Box::new(dev) })
    }

    /// Start a temperature measurement
    ///
    /// # Example
    /// ```
    /// let mut sht20 = SHT20::new("/dev/i2c-3").unwrap();
    /// let temp:f32 = sht20.temperature().unwrap();
    /// ```
    pub fn temperature(&mut self) -> Result<(f32), Box<LinuxI2CError>> {
	self._reset()?;
        self.dev.smbus_write_byte(SHT20_TEMP_HM)?;
        thread::sleep(Duration::from_millis(TEMPERATURE_DELAY));
        self._change_register(SHT20_TEMP_HM)?;
        let msb: u8 = self.dev.smbus_read_byte()?;
        let lsb: u8 = self.dev.smbus_read_byte()?;

        Ok(-46.85 + 175.72 * ((msb as f32) * 256.0 + (lsb as f32)) / 65536.0)
    }


    /// Start a humidity measurement
    ///
    /// # Example
    /// ```
    /// let mut sht20 = SHT20::new("/dev/i2c-3").unwrap();
    /// let hum:f32 = sht20.humidity().unwrap();
    /// ```
    pub fn humidity(&mut self) -> Result<(f32), Box<LinuxI2CError>> {
	self._reset()?;
        self.dev.smbus_write_byte(SHT20_HUMID_HM)?;
        thread::sleep(Duration::from_millis(HUMIDITY_DELAY));
        self._change_register(SHT20_HUMID_HM)?;
        let msb: u8 = self.dev.smbus_read_byte()?;
        let lsb: u8 = self.dev.smbus_read_byte()?;

        Ok(-6.0 + 125.0 * ((msb as f32) * 256.0 + (lsb as f32)) / 65536.0)
    }


    pub fn _reset(&mut self) -> Result<(), Box<LinuxI2CError>> {
        self.dev.smbus_write_byte(SHT20_RESET)?;
        thread::sleep(Duration::from_millis(SOFT_RESET_DELAY));
        let mut _resolution: u8 = RESOLUTION_12BITS;
        let _onchip_heater:u8 = _DISABLE_ONCHIP_HEATER;
        let _otp_reload: u8 = _DISABLE_OTP_RELOAD;

        self._change_register(SHT20_READ_USER_REG)?;
        let mut config: u8 = self.dev.smbus_read_byte()?;
        config = (config & _RESERVED_BITMASK) | _resolution | _onchip_heater | _otp_reload;
        //self.dev.smbus_write_byte(SHT20_WRITE_USER_REG)?;
	//thread::sleep(Duration::from_millis(1000));
        //self.dev.smbus_write_byte(config)?;
	self.dev.smbus_write_byte_data(SHT20_WRITE_USER_REG, config)?;
        Ok(())
    }

    pub fn _write_register(&mut self, register: u8, f_val: f32) -> Result<(), Box<LinuxI2CError>> {
        unsafe {
            let buf: [u8; 4] = mem::transmute(f_val);
            self._change_register(register)?;
            self.dev.smbus_write_byte_data(register + 0, buf[0])?;
            thread::sleep(Duration::from_millis(10));
            self.dev.smbus_write_byte_data(register + 1, buf[1])?;
            thread::sleep(Duration::from_millis(10));
            self.dev.smbus_write_byte_data(register + 2, buf[2])?;
            thread::sleep(Duration::from_millis(10));
            self.dev.smbus_write_byte_data(register + 3, buf[3])?;
            thread::sleep(Duration::from_millis(10));
            Ok(())
        }
    }

    pub fn _read_register(&mut self, register: u8) -> Result<(f32), Box<LinuxI2CError>> {
        let mut buf: [u8; 4] = [0; 4];
        self._change_register(register)?;
        buf[0] = self.dev.smbus_read_byte()?;
        thread::sleep(Duration::from_millis(10));
        buf[1] = self.dev.smbus_read_byte()?;
        thread::sleep(Duration::from_millis(10));
        buf[2] = self.dev.smbus_read_byte()?;
        thread::sleep(Duration::from_millis(10));
        buf[3] = self.dev.smbus_read_byte()?;
        thread::sleep(Duration::from_millis(10));
        Ok(LittleEndian::read_f32(&buf))
    }

    pub fn _change_register(&mut self, register: u8) -> Result<(), Box<LinuxI2CError>> {
        self.dev.smbus_write_byte(register)?;
        thread::sleep(Duration::from_millis(10));
        Ok(())
    }
}
