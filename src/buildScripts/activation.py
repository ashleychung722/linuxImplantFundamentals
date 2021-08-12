import csv
from netaddr import IPNetwork, IPAddress
import random
import subprocess
import sys
import time

targetNetwork = sys.argv[1] #this would be from user argument in compiler.py
numKnockFlag = 0
portKnockFlag = 0
checkDNSFlag = 0
checkURLFlag = 0
revShellFlag = 0
downFlag = 0
sleepFlag = 0

        
def portKnock(ip, key):
        print("portknock")
        count = 0
        
        listOfNumbers = key.split(",")
        
        activateCommand = "nc -z " + ip 
        for i in listOfNumbers:
            activateCommand += " " + str(i)
            
            print(activateCommand)
            subprocess.Popen(activateCommand, shell=True)
        

def listenerSetup(ip, port, platform, arch):
  with open('log.csv') as csv_file:
    next(csv_file)
    csv_reader = csv.reader(csv_file, delimiter='\t')
    #line_count = 0
    #for row in csv_reader:
    for count, row in enumerate(csv_reader):
        if count % 2 != 0:
            continue
        else:
            ip = row[1] 
            ip = ip.lstrip().rstrip()
            if ip != "unknown":
                if IPAddress(ip) in IPNetwork(targetNetwork):
                    if row[7] == "listener":
                        print(row[7])
                        
                        if row[8] == "SECRET_PORTS":
                            print(row[8])
                            portKnockFlag = 1
                    #if row[7] == "checkDNS":
                        #checkDNSFlag = 1
                    #if row[7] == "checkURL":
                        #checkURLFlag = 1
                    #if row[19]:
                        #revShellFlag = 1
                    #if row[17]:
                        #downFlag = 1
                else:
                    print("No!")
            
                    
            #if revShellFlag == 1: 
                #listenerSetup(row[20], row[21], row[4], row[3])               
            #if downFlag == 1:
                #print("Did you set up the file you want run at " + row[17] + "?")
                
            #if sleepFlag == 1:
                #print("Have you waited longer than " + row[0] + "+ sleep(" + row[12] + ")")
                
            
            if portKnockFlag == 1:
                #portKnock(row[1], row[10], row[11])
                print("hello2")
                portKnock(//ip address, // portnumbers )
            '''
            if checkDNSFlag == 1:
                print("Does the domain resolve?")   
            if checkURLFlag == 1:
                print("Does the URL exist?")
            '''
            # Reset all flags for next line in file 
            numKnockFlag = 0
            portKnockFlag = 0
            checkDNSFlag = 0
            checkURLFlag = 0
            revShellFlag = 0
            downFlag = 0 
            sleepFlag = 0
                
            