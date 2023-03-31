#This script generate a certificate in a format that can be used in the ESP32 arduino code
CERTIFICATE = "Builtin Object Token_ISRG Root X1"
def gettext(text):
    for row in text:
        print('"', end='')
        print(row.replace("\n", ""), end="")
        print(r'''\n" \ ''')

if __name__ == "__main__":
    with open(CERTIFICATE, "r") as file:
        text = file.readlines()
        gettext(text)