## Goal
Please write a tool to break a /etc/shadow line using dictonary attack.
Download the dictionary file at:
https://nmsl.cs.nthu.edu.tw/images/courses/CS5432_2016/john.txt .
Your tool will load this dictionary into memory, and tries to concatenate three words into the plaintext password candidate.
Use the crypt library to find the actually password of a person. You need to submit both your source file and library.

## Test Data
–  bear:$6$naIJPKfO
    $SMkeSkFM36M6u3mZIyf2hAr31WxuYtoTwLMjF9Fv49cprYPKtR1K88
    Ox5xvQdLdoBrAOmCnomRvaHc7VDiqQ0:17099:0:99999:7:::
