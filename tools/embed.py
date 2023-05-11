# Copyright (C) 2023 sgf4
#
# This file is part of lostcpp.
#
# lostcpp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# lostcpp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with lostcpp.  If not, see <http://www.gnu.org/licenses/>.

import sys
import os
import random
import string
import hashlib

chunk_size = 1024
current_path = os.path.dirname(__file__)
embed_path = current_path + '/../src/embeds/'

def getcppname(path):
    return embed_path + os.path.basename(path).replace('.', '_') + '.cpp'

def getsum(path):
    with open(path, 'rb') as f:
        bytes = f.read() # read entire file as bytes
        readable_hash = hashlib.sha256(bytes).hexdigest();
        return readable_hash

def embed(path):
    output_cpp_path = getcppname(path)
    ipath = path.split('/res/')[1]
    name = ipath.replace('/', '_').replace('.', '_')
    sum = getsum(path)
    if os.path.exists(output_cpp_path):
        with open(output_cpp_path, 'r') as f:
            if f.readline().split('// ')[1].strip() == sum:
                return

    with open(path, 'rb') as f:
        with open(output_cpp_path, 'w') as output_cpp:
            passwd = ''.join([random.choice(string.digits + string.ascii_letters) for i in range(16)])
            output_cpp.write(f'// {sum}\n')
            output_cpp.write('#include <embed.hpp>\n')
            output_cpp.write(f'constexpr CompTimeStr {name}_pw {{"{passwd}"}};\n')
            output_cpp.write(f'u8 {name}[] {{')

            while 1:
                chunk = f.read(chunk_size)
                if not chunk:
                    break
                output_cpp.write(''.join([str(chunk[i] ^ ord(passwd[i % len(passwd)])) + ',' for i in range(len(chunk))]))

            output_cpp.write(f'0x00}};\n')
            output_cpp.write(f'template<> Embed embed<"{ipath}"> {{ {name}, {name}_pw.data}};')

if not os.path.isdir(embed_path):
    os.mkdir(embed_path)

for path in sys.argv[1:]:
    embed(path)
