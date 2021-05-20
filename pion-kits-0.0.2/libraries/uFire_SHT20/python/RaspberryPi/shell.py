import cmd
from SHT20 import SHT20

sht20 = SHT20()

class SHT20Shell(cmd.Cmd):
        prompt = '> '

        def do_temperature(self, a):
                print("%.2f" %sht20.temperature())


        def do_humidity(self, a):
                print("%.2f" %sht20.humidity())

SHT20Shell().cmdloop()