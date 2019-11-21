import cstruct

class user(cstruct.CStruct):
    __byte_order__ = cstruct.LITTLE_ENDIAN
    __struct__ = """
    char username[64];
    char password_salt[8];
    char password_hash[64];
    char favorite_drink[128];
    char super_power[128];
    char weakness[128];
"""

def main():
    tom = user()
    tom.username = "Tom Cat"
    tom.password_salt = "yhfe"
    tom.password_hash = "f3e596b63ae779f278a9a6fe905cda03"
    tom.favorite_drink = "soda"
    tom.super_power = "Super strength"
    tom.weakness = "Intelligence"

    jerry = user()
    jerry.username = "Jerry Mouse"
    jerry.password_salt = "7yts"
    jerry.password_hash = "ca63ecde5c89dbc73a563eaf825e59c7"
    jerry.favorite_drink = "milk"
    jerry.super_power = "Bat Mouse"
    jerry.weakness = "Size"

    with open('test.bin', 'wb') as fp:
        fp.write(tom.pack())
        fp.write(jerry.pack())

if __name__ == '__main__':
    main()