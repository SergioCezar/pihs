print('======Distancia de Levenshtein:======')
strings = [
    'casa casca',      
    'gato rato',         
    'kit kat',           
    'intenção atenção',
    'monitor computador',
    'python java',
    'programação informática'   
]
for i in range(len(strings)):
    stringa, stringb = strings[i].split(' ')
    distancia = dist_levenshtein(stringa, stringb)
    print('A distancia entre ' + stringa + ' e ' + stringb + ' é: ' + str(distancia))

print('======Distancia de Hamming:======')

strings = [
    'aaaaa aaaab',    
    '12345 54321',    
    'abcde abfde',   
    'karla karlo',
    'a bb'     
]
for i in range(len(strings)):
    stringa, stringb = strings[i].split(' ')
    distancia = dist_hamming(stringa, stringb)
    print('A distancia entre ' + stringa + ' e ' + stringb + ' é: ' + str(distancia))