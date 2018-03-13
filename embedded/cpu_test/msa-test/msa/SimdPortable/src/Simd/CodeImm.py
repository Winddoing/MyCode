#!/usr/bin/env python
def main():
    for i in range(-512,512):
        print("Template(Func,OP,%d,CODE);\t" % i),
        if i % 4 == 3:
            print "\\"
    print ""
if __name__ == '__main__':
    main()
