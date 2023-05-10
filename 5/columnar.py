def columnar_encryption(text, key):
  ct = ''
  arr = [[None for i in range(len(key))] for j in range(len(key))]

  k = 0
  for i in range(len(key)):
    for j in range(len(key)):
      if k < len(text):
        arr[i][j] = text[k]
        k +=1
      else:
        arr[i][j] = 'X'
 
  for i in key:
    for j in range(len(key)):
      
      ct += arr[j][int(i)-1]
  return ct, arr
  
def columnar_decryption(ct, key):
  text = ''
  arr = [[None for i in range(len(key))] for j in range(len(key))]
  k = 0
  for i in key:
    for j in range(len(key)):
      if k < len(ct):
        arr[j][int(i)-1] = ct[k]
        k +=1
      else:
        arr[i][j] = ''
  print(arr)
  for i in range(len(key)):
    for j in range(len(key)):
      if arr[i][j] != 'X':
        text += arr[i][j]
  
  return text, arr


text = input("Enter the message: ")
n = input("Enter the key: ")
encrypt_message=columnar_encryption(text, n)
print("Encode Text: ",encrypt_message[0])

print("Decode Text: ",columnar_decryption(encrypt_message[0],n)[0])