#!/usr/bin/env python3

import functools
import hashlib
import itertools
import multiprocessing
import os
import string
import sys

# Constants

ALPHABET    = string.ascii_lowercase + string.digits
ARGUMENTS   = sys.argv[1:]
CORES       = 1
HASHES      = 'hashes.txt'
LENGTH      = 1
PREFIX      = ''

# Functions

def parseCommands(args):
    flags = {}
    if args[0] == '-h':
        usage()
    else:
        while args:
            if args[0][0] == '-':
                flags[args[0]] = args[1]
            args = args[1:]
    return flags

def usage(exit_code=0):
    print('''Usage: {} [-a alphabet -c CORES -l LENGTH -p PREFIX -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file'''.format(os.path.basename(sys.argv[0])))
    sys.exit(exit_code)

def sha1sum(s):
    hash_object = hashlib.sha1(s.encode())
    hex_dig = hash_object.hexdigest()
    return hex_dig

def permutations(length, alphabet=ALPHABET):
    if length == 1:
        for i in alphabet:
            yield i
    else:
        for i in alphabet:
            for p in permutations(length - 1, alphabet):
                yield i+p


def smash(hashes, length, alphabet=ALPHABET, prefix=''):
    perms = (prefix + p for p in permutations(length, alphabet))
    return [password for password in perms if sha1sum(password) in hashes]

# Main Execution

if __name__ == '__main__':
    myargs = parseCommands(ARGUMENTS)
    if '-h' in myargs:
        usage()
    if '-a' in myargs:
        ALPHABET = myargs['-a']
    if '-c' in myargs:
        CORES = int(myargs['-c'])
    if '-l' in myargs:
        LENGTH = int(myargs['-l'])
    if '-p' in myargs:
        PREFIX = myargs['-p']
    if '-s' in myargs:
        HASHES = myargs['-s']

    hashSet = set(map(lambda s: s.strip(), open(HASHES)))
    if CORES > 1 and LENGTH > 1:
        subsmash = functools.partial(smash, hashSet, LENGTH - 1, ALPHABET)
        prefixes = [PREFIX+a for a in ALPHABET]
        pool = multiprocessing.Pool(multiprocessing.cpu_count())
        passwords = itertools.chain.from_iterable(pool.imap(subsmash, prefixes))
    for passwords in smash(hashSet, LENGTH, ALPHABET, PREFIX):
        print(passwords)


# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
