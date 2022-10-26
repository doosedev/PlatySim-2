# -*- coding: utf-8 -*-
"""
Created on Sun Dec 5 00:25:04 2021

@author: Perry
"""
# import csv and matplotlib
import csv
import matplotlib.pyplot as plt

# read data.csv into a dictionary called data
data = csv.DictReader(open("sim.csv"))

# split the data into three lists for x, y, and z
dataArrays = {"time": [], "pos_x": [], "pos_y": [], "pos_z": [], "vel_x": [], "vel_y": [], "vel_z": [], "acc_x": [], "acc_y": [], "acc_z": [], "alpha": []}

for row in data:
    for key in dataArrays:
        dataArrays[key].append(float(row[key]))

# Plot x, y, and z velocity
plt.subplot(221)
plt.title("Velocity")
plt.xlabel("Time (s)")
plt.ylabel("Velocity (m/s)")
plt.plot(dataArrays["time"], dataArrays["vel_x"], label="x", color="red")
plt.plot(dataArrays["time"], dataArrays["vel_y"], label="y", color="green")
plt.plot(dataArrays["time"], dataArrays["vel_z"], label="z", color="blue")
plt.grid(True)
plt.legend()

# Plot x, y, and z acceleration
plt.subplot(223)
plt.title("Alpha")
plt.xlabel("Time (s)")
plt.ylabel("Angle of Attack (rad)")
plt.plot(dataArrays["time"], dataArrays["alpha"], label="aoa", color="red")
plt.grid(True)
plt.legend()
"""plt.title("Acceleration")
plt.xlabel("Time (s)")
plt.ylabel("Acceleration (m/s^2)")
plt.plot(dataArrays["time"], dataArrays["acc_x"], label="x", color="red")
plt.plot(dataArrays["time"], dataArrays["acc_y"], label="y", color="green")
plt.plot(dataArrays["time"], dataArrays["acc_z"], label="z", color="blue")
plt.grid(True)
plt.legend()"""

plt.subplot(122, projection='3d')
plt.title("Position")
plt.plot(dataArrays["pos_x"], dataArrays["pos_y"], dataArrays["pos_z"], label="3D Trajectory", color="black")
plt.grid(True)

plt.show()