print('======Distancia de Levenshtein:======')
strings = ['Pao Batata', 'Faculdade Escola', 'Ayrton Senna', 'Pele Maradona']
for i in range(len(strings)):
    stringa, stringb = strings[i].split(' ')
    distancia = levenshtein_em_python(stringa, stringb)
    print('A distancia entre ' + stringa + ' e ' + stringb + ' é: ' + str(distancia))

print('======Distancia de Hamming:======')

strings = ['banana macaco', 'lata vara', 'xica xico', 'leandros leonardo']
for i in range(len(strings)):
    stringa, stringb = strings[i].split(' ')
    distancia = hamming_em_python(stringa, stringb)
    print('A distancia entre ' + stringa + ' e ' + stringb + ' é: ' + str(distancia))