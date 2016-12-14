#!/usr/bin/python
# -*- coding: utf-8 -*-

import bluetooth
import sys
import colorsys

def hsv2rgb(h,s,v):
  return tuple(int(i * 255) for i in colorsys.hsv_to_rgb(h,s,v))

bd_addr = "00:19:5D:EE:A4:24"
port=1
msg = bytearray("\x00\x00\xff\xff\x00;")

if len(sys.argv) != 2:
  print "Donnez-moi une teinte (0-359) !"
  sys.exit(1)

couleur = int(sys.argv[1])

if not (0 <= couleur <= 359):
  print "Mauvaise couleur/teinte !"
  print "Entre 0 et 359 svp."
  sys.exit(1)

print "Envoi..."

try:
  sock=bluetooth.BluetoothSocket(bluetooth.RFCOMM)
  sock.connect((bd_addr, port))
except:
  print "Erreur lors de la connexion !"
  sys.exit(1)

msg[2],msg[3],msg[4] = hsv2rgb(couleur/360.0,1,1)
sock.send(str(msg))

try:
  sock.close()
except:
  print "Erreur lors de la déconnexion !"

