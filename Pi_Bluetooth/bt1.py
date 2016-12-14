#!/usr/bin/python
# -*- coding: utf-8 -*-

import bluetooth
import time
import sys

bd_addr = "00:19:5D:EE:A4:24"
port=1

print "Connexion..."

try:
  sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)
  sock.connect((bd_addr, port))
except:
  print "Erreur lors de la connexion !"
  sys.exit(1)

print "Connecté."

time.sleep(2)

print "Déconnexion..."

try:
  sock.close()
except:
  print "Erreur lors de la déconnexion !"

print "Déconnecté."


