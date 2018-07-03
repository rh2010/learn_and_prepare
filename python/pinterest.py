#!/usr/bin/python3

# 1. Balanced parenthesis
# '(', ')', '{', '}', '[' and ']'
# ([)]
# ([])

# 2. Given a string of un-balanced parenthesis, return the set of
# all balanced parenthesis that can result after minimum deletion
# of parenthesis which makes the string un-balanced.
# ()())()) -> ()()() (())()
   
# )
# ()()
# ()())())

# ()()) ->  ()()(), (())(),

# ()()(), (())(), (()()),  

def solve(string):
    result = []
    stack = []
    
    o = '('
    c = ')'
    last_fix = 0 
    for i, e in enumerate(string):
        mismatch = False
        print("Processing [%d]: %c" % (i, e))
        if e is o:
            stack.append(e)
        if e is c:
            if len(stack) == 0:
                mismatch = True
                # fix mismatch
            else:
                m = stack.pop()
                if m != o:
                    mismatch = True
            print("Stack: \t%s" % (stack))

            if mismatch:
                print("Mismatch")
                new_result = []
                # fix mismatch
                if len(result) == 0:
                    sub_str = list(string[last_fix:i+1])
                    print(sub_str)
                    for ss_e_i, ss_e in enumerate(sub_str):
                        if ss_e is c:
                            print("removing [%d] %c" % (ss_e_i, ss_e))
                            temp = list(sub_str)
                            temp.pop(ss_e_i)
                            #temp.append(')')
                            temps = str(''.join(temp))
                            if temps not in result and temps not in new_result:
                                print("Adding to result: %s" % (temps))
                                new_result.append(temps)
                    result = result + new_result
                else:
                    print("Some strings already in result")
                    print(len(result), result)
                    new_result = []
                    for r in result:
                        print("Processing %s" % (r))
                        ss = string[last_fix:i+1]
                        print("Since last fix: %s" % (ss))
                        rs = r+ss
                        print("Evaluating: %s" % (rs))
                        for ss_e_i, ss_e in enumerate(rs):
                            if ss_e is c:
                                print("removing [%d] %c" % (ss_e_i, ss_e))
                                temp = list(rs)
                                temp.pop(ss_e_i)
                                #temp.append(')')
                                temps = str(''.join(temp))
                                print("Next result %s" % (temps))
                                if temps not in result and temps not in new_result:
                                    print("Adding")
                                    new_result.append(temps)
                                else:
                                    print("Alread present")
                last_fix = i+1
                result = new_result
                print("LastFix: %d" % (last_fix))
                print("Result: \n\t%s" % (result))

    return result
            
        
def validate_paren(string):
    paren_pair = {']' : '[',
                  ')' : '(',
                  '}' : '{'}
    
    if len(string)%2 != 0:
        return False
    
    # list of open parenthesis
    list_open = paren_pair.values()
    
    # list of closed parenthesis
    list_closed = paren_pair.keys()
    
    stack = []
    
    for e in string:
        if e in list_open:
            stack.append(e)
        if e in list_closed:
            # Empty stack
            if len(stack) == 0:
                return False
            match = stack.pop()
            if match != paren_pair[e]:
                return False
            
            
    if len(stack) is 0:
        return True
    
    return False

if __name__=="__main__":
    s="([)]"
    s1="([])"
    s2="([]{}})"
    s3="()())())"
    
    #print(validate_paren(s))
    #print(validate_paren(s1))
    print(s3)
    print(solve(s3))
    
    

