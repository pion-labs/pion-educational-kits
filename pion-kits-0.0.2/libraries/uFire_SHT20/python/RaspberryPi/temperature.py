from SHT20 import SHT20

sht = SHT20()
tempF = sht.temperature() * 1.8 + 32.0
print("%.2f" %tempF)
