Memória virtual - Possuí 1MB
Memória principal 64 - 8 Frames com 8kb cada
Pages - 8kb
Frames - 8kb

Defini um numero máximo de processos para 9

Criação de 3 structs
Page
data - guarda um dado fictício
posPage - seria um id da Page atual - que é a posição dele dentro da memória virtual

Frame
isUsed - boolean para dizer se o Frame atual na mmemória principal está sendo utilizado
posPage - Para saber a posição da Page na memória virtual
name - Para guardar o nome do processo atual

Process
id - Posição do processo no array de processos e o seu nome
initialPosition - Posição onde ele inicia na memória virtual
lastPosition - Posição onde ele acaba na memória virtual
numPages - numero de paginas que ele ocupa na memória virtual
dataAmount - tamanho do Processo
found - boolean para verificar se o processo existe para busca por id

Assinaturas de funções

virtualMemo - Vetor de Pages
principalMemo - Vetor de Frames
processes - vetor para guardar os Processos
lastPosition = variável auxiliar para controlar a última posição de cada processo
values = vetor auxiliar para setar valores no dataAmount e inicializar o processo

populateVirtualMemory
Ele vai fazer um loop pela quantidade de NUMBER_PROCESSES
chamar a função newProcess
Passando 
i -> que vai ser o nome/id do processo
values[i] -> tamanho do processo
Esse processo criado vai ser salvo dentro vetor de processos

newProcess
Função recebe:
id -> seta o nome/id do processo
initialPosition -> Guarda o valor atual da variável lastPosition
numberPages -> Chama a função verifyNumberOfPages para verificar quantas páginas são necessárias para o tamanho do processo recebido
lastPosition -> Define o valor a partir do initialPosition mais o numPages do processo
dataAmount -> Guarda o tamanho do processo
found -> Para futuras buscar pelo processo. Define o valor para false

saveProcess
Salva o processo dentro de um array de Pages
Função recebe:
Um processo

Loop vai percorrer a memória virtual
Loop vai até o numero de Pages já calculado e guardado dentro do atribuito numPages do processo
Para cada Page
Guarda valor ficticios em data 
Aloca o processo na memória virtual em LastPosition + mais valor de i no loop atual

findProcessById
Função de busca de um processo
É passado o nome/id do processo

Loop no array de processos para procurar pelo nome/id
Quando encontra 
Altera o valor de found no processo encontrado para true

e retorna o processo


verifyNumberOfPages
Recebe o tamanho do processo
verifica se o tamanho do processo dividido pelo tamanho de Pages 8kb tem resto 0
Se não pega o resultado da divisão e acrescenta mais 1
Retorna esse numero para ser o numero de páginas

verifyPrincipalMemoryUsed
Verifica se a Page de algum processo está utilizando a memória Principal
E informa o nome do processo e qual frame está utilizando

verifyNextEmpty
Método auxiliar para verificar
se algum frame está vazio
Retorna o numero do Frame vazio se existir
se não -1

listProcesses
List todos os processos e seus nomes/ids

mapVirtualToPrincipal
Utiliza-se a função findProcessById
Onde é passado o nome do Processo a ser mapeado da memória Virtual para a memória Principal
Caso o Processo não exista retorna que o processo nao foi encontrado

Caso exista
Informa que o processo foi encontrado
Utiliza-se a função verifyNextEmpty
Para saber se existe um espaço na memória Principal vazio

Loop do posição inicial mais uma variavel auxiliar count até a última posição
Testa se cada iteração do loop já passou da ultima posição da memória Principal
caso Não 
chama a função verifyPrincipalMemoryUsed
Para saber se alguem está utilizando o frame atual
Caso esteja sendo usada, informa o frame atual e qual o nome do processo que está utilizando
Faz um mapping da Posição da Page na memória Virtual
Define o valor isUsed no frame para true
Guarda o nome do processo atual em nameProcess
Retorna uma mensagem das informações definidas no Frame

Caso chegue na último frame
Ele quebra o loop dos frames
Porém se ainda não chegou no fim das Pages a serem mapeadas
Ele reinicia o loop 
Para mapear a partir do primeiro frame

count -> variavel auxiliar para controlar o loop do mapeamento de Pages

Define o valor de processo found para false


showProcess
A partir do nome do processo 
Verifica se ele existe a partir da função findProcessById
Imprime o nome do processo, sua posição na memória Virtual e nome de Pages que ocupa

mapAllProcessToPrincipal
Passa todos o processos por um loop
Chamando para cada a função mapVirtualToPrincipal

clearPrincipalMemory
Função que limpar todos os Frames da memória Principal
Altera o atributo isUsed de todos frames para false;

menu
Menu de opções
loop para enquanto a opção não for a de saida 0

main
Criação da memória Virtual e a Principal
chama o método populateVirtualMemory para popular a memória principal
chama o menu

Libera a memória utilizada pela memória Virtual e memória Principal









