import re

f_input = open("macro_input.txt")
inputcode = list(line.strip() for line in f_input)
MDT = []
MNT = {}
ALA_list = {}
input_for_pass_2 = []
iterator = iter(inputcode)

while True:
    try:
        line = next(iterator)
        if line == "MACRO":
            nameline = next(iterator)
            nameline = re.split('[,\s]', nameline)
            macro_name = ""
            for token in nameline:
                if "&" not in token:
                    macro_name = token
                    break
            MNT[macro_name] = len(MDT)
            ALA = {}
            arg_counter = 0
            for token in nameline:
                if token is not macro_name:
                    arg_counter += 1
                    ALA[token] = "#" + str(arg_counter)
                    nameline[nameline.index(token)] = ALA[token]
            ALA_list[macro_name] = ALA
            MDT.append(nameline)
            
            while True:
                macroline = next(iterator)
                for argument in ALA.keys():
                    if argument in macroline:
                        macroline = macroline.replace(argument, ALA[argument])
                MDT.append(macroline)
                if macroline == "MEND":
                    break
        else:
            input_for_pass_2.append(line)
    except StopIteration:
        break

print("\nMNT is ")
for line in MNT.items():
    print(line)
print("\nMDT is ")
for line in MDT:
    print(line)
print("\nALAs are ")
for line in ALA_list.items():
    print(line)

iterator = iter(input_for_pass_2)
print("\nFinal Output is ")

while True:
    try:
        line = next(iterator)
        line = re.split('[,\s]', line)
        if any(word in line for word in MNT.keys()):
            macroname = ""
            if line[0] in MNT.keys():
                macroname = line[0]
            else:
                macroname = line[1]
            label = line[0]
            actual_args = []
            for token in line:
                if not token == macroname:
                    actual_args.append(token)
            
            ALA = ALA_list[macroname]
            ALA = {val: key for key, val in ALA.items()}
            
            formal_args = sorted(list(ALA.keys()))
            
            for i in range(len(formal_args)):
                ALA[formal_args[i]] = actual_args[i]
            
            MDTP = MNT[macroname] + 1
            
            while "MEND" not in MDT[MDTP]:
                line = MDT[MDTP]
                
                for formal_arg, actual_arg in ALA.items():
                    line = line.replace(formal_arg, actual_arg)
                
                print(line)
                MDTP += 1
                
        else:
            print(" ".join(line))
                
    except StopIteration:
        break
