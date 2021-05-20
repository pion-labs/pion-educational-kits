extern crate ufire_sht20;
extern crate shrust;
use shrust::{Shell, ShellIO};
use std::io::prelude::*;
use ufire_sht20::*;

fn main() {
	println!("Isolated EC Probe Interface shell");
	println!("type `help` for a list of commands");
	let mut shell = Shell::new(());

	shell.new_command_noargs("t", "Measure temperature", move |io, _| {
		let mut sht20 = SHT20::new("/dev/i2c-3").unwrap();
		try!(writeln!(io, "{}", sht20.temperature().unwrap()));
		Ok(())
	});

	shell.new_command_noargs("h", "Measure humidity", move |io, _| {
		let mut sht20 = SHT20::new("/dev/i2c-3").unwrap();
		try!(writeln!(io, "{}", sht20.humidity().unwrap()));
		Ok(())
	});

    shell.run_loop(&mut ShellIO::default());
}
