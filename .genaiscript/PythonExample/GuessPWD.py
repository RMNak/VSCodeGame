from random import *
import os
import platform

u_pwd = input("Enter password  ")

pwd = ['a', 'b', 'c','d', 'e','f','g','h','i','j','k','l','m','n','o','p','q','r,','s','t','u','v','w','x','y', 'z','1','2','3','4','5','6','7','8','9','0','@','$']

def getWindowsVersion():
    w_version = platform.version()
    print("Version of windows is = ", w_version)


def matchChar(c):
    """
    Matches a character `c` with a randomly selected character from the `pwd` string.

    Parameters:
    c (str): The character to be matched.

    Returns:
    str: The matched character from the `pwd` string.

    """
    print(c)
    while (True):
        r1 = randint(0, len(pwd)-1)
        if(pwd[r1] == c):
            return str(pwd[r1])

g_pwd = ""
for c in range(len(u_pwd)):
    found = matchChar(u_pwd[c])
    print("found char == > ",  found)
    g_pwd = str(g_pwd) + str(found) 
    print("cracking password .. please wait")
    os.system("cls")        

print("your password is = ", g_pwd)
getWindowsVersion()