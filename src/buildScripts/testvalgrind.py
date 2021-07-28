import subprocess


cmd = ["valgrind", "--leak-check=full", "./compiler.py"]
subprocess.run(cmd)

#valgrind --leak-check=full ./compiler.py
