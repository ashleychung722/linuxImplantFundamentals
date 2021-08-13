import subprocess


cmd = ["valgrind", "--leak-check=full", "python3", "compiler.py"]
subprocess.run(cmd)

#valgrind --leak-check=full ./compiler.py