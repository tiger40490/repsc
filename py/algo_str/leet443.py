'''
findall() is NOT useful when leetcode requirement is stringent like O(1) space. With those requirmeents, you need to write low-level code that's similar in C, java or python

To satisfy O(1) space, need to overwrite CHARS array. Use 2 markers. Front marker is for reading the original input; back marker is where to write the output into the same array.
'''
import itertools
# ------------solution 1 based on Alina ------------
def groupby(chars): # breaks O(1) space 
    result_list = []
    for k, consecutiveItems in itertools.groupby(chars):
        cnt = len(list(consecutiveItems))
        result_list.append(k)
        if cnt==1: pass 
        else: 
            result_list.extend(list(str(cnt)))
    #print(result_list)
    ret = len(result_list)
    chars[:ret] = result_list
    print chars
    return ret
def main():
  assert 5==groupby(list('abbccc'))
  assert 6==groupby(list('aabbccc'))
  assert 1==groupby(list('a'))
  assert 4==groupby(list('abbbbbbbbbbbb'))
  assert 6==groupby(list('aaabbaa'))
main()  
'''Req: https://leetcode.com/problems/string-compression/
There are two outputs:
1) the function need to return an integer
2) the function need to modify (in place) the input list, replacing the left portion with the compression result_list

'''