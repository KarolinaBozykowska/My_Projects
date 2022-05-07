# -*- coding: utf-8 -*-
"""
Created on Sat May  7 18:01:17 2022

@author: Karolina Bozykowska

Write a program that will calculate the cost of a custom cup of coffee at a gourmet coffee shop, based on the size of the cup, the type of coffee selected, and flavors that can be added to the coffee.
"""
price = 0
small = "$2"
medium = "$3"
large = "$4"
brewed = "$0" 
espresso = "$0.50"
cold_brew = "$1"
flav = "$0.50"
print("We are offering 3 sizes of coffee: small for",small, "medium for", medium, "and large for", large)
cussize = input("Please choose size of your coffee: ")
cussize = cussize.lower()
if not (cussize=="small" or cussize=="medium" or cussize=="large"):
    print("Wrong size, please type correct size")
    cussize = input("Choose correct size of your coffee")
print("We have 3 types of coffee: brewed with no extra costs, espresso for", espresso, "extra and cold brew for", cold_brew, "extra")
custype = input("Please choose your type: ")
custype = custype.lower()
if not (custype=="brewed" or custype=="espresso" or custype=="cold brew"):
    print("Wrong type, please type correct type")
    custype = input("Choose correct type of your coffee")
print("Do you want flavoured syroup for extra", flav, "in your coffee?")
cusflav = input("Yes or no? ")
cusflav = cusflav.lower()
if (cusflav == "yes"):
    flavour = input("hazelnut, vanilla or caramel?")
if (cusflav == "yes"):
    print("Your order is", flavour, cussize, custype, "coffee")
else:
    print("Your order is no flavoured", cussize, custype, "coffee")
if (cussize == "small"):
    price+=2
if (cussize == "medium"):
    price+=3
if (cussize == "large"):
    price+=4
if (custype == "brewed"):
    price+=0
if (custype == "espresso"):
    price+=0.50
if (custype == "cold brew"):
    price+=1
if (cusflav == "no"):
    price+=0
if (cusflav == "yes"):
    price+=0.5
print("Cost of your coffee is $", price)
print("Total price of your coffee with tip is $", round((price + 0.15*price), 2))
