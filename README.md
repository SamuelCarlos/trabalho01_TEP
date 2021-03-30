# Trabalho Prático  I - TEP - UFLix 
Prof. Vinicíus Mota 
DI/UFES

**Data de entrega: 11/04/2021**
Locais de entrega:
 - submetido pelo Repl.it; 
 -  E também pelo AVA.

## 1. Objetivos

Este primeiro trabalho visa o desenvolvimento das habilidades de criação de tipos abstratos de dados, bibliotecas, organização e documentação correta de código, gerenciamento de memória e compilação automática de código.  Para isto, o objetivo deste trabalho é o desenvolvimento de um sistema de gerenciamento e visualização de filmes.  Considere um sistema de streaming simples de filmes no terminal, capaz de listar, adicionar, pesquisar filmes.   As funcionalidades e especificações do sistema (quanto a formato de arquivos, como compilar, etc.) seguem nesse arquivo, mas estão sujeitas a mudanças:

  ## 2. Descrição do sistema

O objetivo deste trabalho é simular um serviço de streaming de vídeos.  Para isto, o usuário do programa deve ter uma conta que contem login e senha.  Após o login, o programa cliente carregará um catálogo de filmes disponíveis e o usuário poderá selecionar um filme para "assistir". O catálogo de filmes deve ser armazenado em um arquivo com os metadados dos filmes, arquivo explicado posteriormente.

O usuário deve ser capaz de visualizar a lista de filmes disponíveis, as informações sobre os filmes (metadados), pesquisar por um filme e escolher um filme para assistir. Deve ser feito o tratamento da entrada do usuário, para caso o usuário digite alguma opção inválida o programa saiba lidar com isso.  Para cada filme "assistido", o usuário pode atribuir uma nota ao filme.  

Os filmes assistidos devem ser salvos em um histórico. O histórico contém a data que o filme foi assistido e a nota que o usuário deu para aquele filme. O usuário pode exibir o histórico ordenado por data ou por nota, de forma descendente, isto é, do mais recente/melhor avaliado para o mais antigo/pior avaliado.

**IMPORTANTE**:

 - O código deve ser devidamente separado em bibliotecas com os devidos cabeçalhos e implementações, sempre levando em consideração as boas práticas.  
 - É responsabilidade do desenvolvedor garantir que o programa faz uso eficiente da memória. 
 - É seu dever  como desenvolvedor filtrar erros de entrada dos usuários. Mesmo que não estejam listados aqui. Sempre comente essas verificações.
 - A compilação do executável deve ser por meio de um Makefile.
 - Código deve estar bem comentado.
 - É opcional "limpar o terminal" entre as passagens do menu de opções. 
 - O programa deve ser iniciado com um inteiro que indica a "verbosidade" do programa, isto é, se os menus serão imprimidos ou se apenas a saída será imprimida no terminal.


### 2.1 Funcionalidades

  

O programa funcionará com uma interface do usuário com o sistema. Isso deve ser feito no terminal a partir da leitura de números que representam decisões do usuário. Considere que ao iniciar o programa o usuário pode indicar se ele quer que o menus sejam impressos ou não.

A Figura abaixo apresenta de forma sumarizada todas as funcionalidade que o sistema deve conter:

![enter image description here](diagramaUflix.png)

Ao executar o programa, deve ser carregado na memória a lista de filmes disponíveis e os usuários cadastrados. O Formato dos arquivos é discutido na próxima seção.

### 2.1.1 Menu Login

A  primeira "tela" que o usuário deve ver é uma tela de login com as opções:


    
    1- Login
    2- Cadastrar
    3- Sair

#### Opção 1 - Login

Quando o usuário entrar a opção 1, recebe 2 strings como entrada. Por exemplo:


    1
    joao
    123456

 O programa deve comparar o usuário e senha com os carregados pelo arquivo usuarios.csv. Três condições podem ocorrer:
  
  1. Se usuário existe e senha correta, vai para o menu principal.
  2. Se usuário não existe, exibe a mensagem abaixo e volta ao menu anterior.

    Usuario nao cadastado.    
  
  3. Se usuário existe e a senha está incorreta, exibe a mensagem abaixo e volta ao menu anterior.
    
    Senha incorreta.    


#### Opção 2 - Cadastrar usuário

 Permite cadastrar usuários. Para cada cadastro é necessário inserir nome e senha.  Como no exemplo:
 

    Usuário: <entrada>
    Senha: <entrada>
    Confirmar senha: <entrada>

**Regras para nome e senha de usuário**:
 -  Usuario e senha são strings alfanumericas de qualquer tamanho mas não contêm acentos e nem espaços.
 - O programa deve verificar que não existe usuário com mesmo nome já cadastrado.
 - Deve-se garantir que a confirmação da senha é igual a senha. 
 
Caso contrário, exibir as respectivas mensagens de erro e voltar ao menu anterior:
  
    Senha fora do padrao.
    Usuario ja cadastrado.
    Senha incorreta.    

#### Opção 3 - Sair

Sempre que o usuário sair do programa pelo menu, deve-se garantir que quaisquer dados que precisam ser persistidos já foram salvos em arquivos. Por exemplo, adicionou um novo usuário no arquivo de usuários  ou um filme ao histórico do usuário. 

Além disso, é dever do desenvolvedor  garantir que toda a memória foi liberada.  Vazamentos de memória serão penalizados.

### 2.1.2 Menu principal

Caso o login esteja correto, o programa vai para o Menu principal que contém as seguintes opções:

    1- Listar filmes
    2- Meu perfil
    3- Procurar Filme
    4- Sair

#### Opção 1 - Lista de filmes

Exibe a lista de filmes disponíveis, exibindo um identificador e o título do filme e aguarda uma entrada do usuário.


    1- <filme1>
    2- <filme2>
    ...
    <entrada esperada>
    id do filme que deseja assistir
    M - Mais filmes
    0- Voltar

Considerando que o número de filmes a serem exibidos pode ser grande demais, deverá ser definido um limite de títulos a  serem exibidos. 


Para exemplificar, suponha que a base contenha 100 filmes e o limite de exibição é de 10 filmes.  Serão listados os filmes de 1 a 10, se usuário entrar a opção *M*, são mostrados os filmes de 11 a 20 e por aí vai. Caso não tenha mais filmes a serem listados a opção M exibe a mensagem 

    Fim de filmes disponiveis


Se o usuário digitar um inteiro maior que zero, assume-se que trata-se de um  filme que se deseja assistir. 

Após o usuário digitar a entrada com o filme desejado, são exibidas Informações sobre o filme (exemplo do primeiro filme do arquivo de filmes  `filmes-grande.csv`):

    Titulo: Amazing Stories
    Ano: 1986
    Duração: 111 minutos
    Avaliação: 7.2
    Descrição: A compilation of episodes from the anthology SF/Fantasy TV series.

    1- Assistir
    2- Voltar 
    <entrada>

Ao assistir o filme, **opção 1**, é solicitado sua avaliação (float) e a data em que foi assistido (string no formato dd/mm/yyyy):

    O que achou de Amazing Stories? De uma nota entre 0 e 10:
    <entrada>
    Data: <entrada>


#### Opção 2 - Meu perfil:

As seguintes opções são mostradas:

    D ou N- Histórico ordenado por data ou por Nota
    2. Excluir minha conta
    <entrada>
    3. Voltar

Caso o usuário entre com as opções *D* ou *N*, é apresentado o histórico de filmes que o usuário assistiu. Contendo data, título e avaliação dada para o filme. Sendo que a opção *D* apresenta o histórico ordenado por data do mais recente para o mais antigo  e a opção *N* apresenta o histórico ordenado por nota, da maior para a menor.

    Nome: joao
    Meu historico:
        28/03/2021 - Amazing stories: Sem avaliacao
        <data2> - <filme2>: <avaliacao2>
   

A opção 2  - Permite excluir a conta do usuário. A exclusão pode ser apenas marcando uma  conta como inativa. Neste caso, a conta não precisa ser excluída, mas apenas marcada como inativa, impedindo que alguém logue nela e permitindo que uma nova conta com mesmo usuário seja criada. A solução de apenas inativar a conta leva a modificações no login, que passa a ter que verificar se uma conta é ativa ou não.

### 2.2. Verbosidade (verbosity)

Verbosidade é quanto de saída um programa gera. Esse conceito é amplamente utilizado para se ter uma versão de depuração de programas e outra para produção.  

Neste trabalho, verbosidade vai indicar se os menus apresentados na seção anterior serão exibidos ou não. 

Considere que o seu programa vai receber como argumento um inteiro 0 ou 1 que indica a verbosidade, exemplo `./tp 1` ou `./tp 0`.

Caso o argumento seja 1, os menus são exibidos conforme descrito nas seções anteriores. Caso o argumento seja 0, o programa recebe as entradas do usuário e apenas imprime a saída final, se tiver. Por exemplo, dar nota a um filme sem exibir os menus:
```
<entrada>
./tp 0
1 
joao
123456
1
```
```
<saída>
<<Lista de filmes>>
```
```
<Continuação entrada>
1
```
```
<saída>
<<Metadado do filme 1>>
```

## 3. Arquivos de entrada

O sistema realiza a leitura de dois arquivos `.csv`: o arquivo de usuários e o de filmes. Suas informações são separadas por vírgula simples.

Para o arquivo de filmes, são dispostas as informações

    título,ano,duração_mins,nota,descrição
    
onde título e descrição são strings de, no máximo, 128 e 256 caracteres respectivamente, duração é um inteiro e nota é um float.

Para o arquivo de usuários, são dispostas as informações

    usuário,senha,histórico1,avaliação1,histórico2,avaliação2,...

em que usuário e senha são strings, históricos são inteiros que representam o id de um filme (que é apenas a linha correspondente do filme no respectivo arquivo) e avaliação é uma nota dada ao filme pelo usuário (notas negativas significam que o usuário não avaliou o filme quando assistiu).

**Vale lembrar:** o campo de descrição (e apenas o de descrição) pode conter vírgulas! Nesse caso, o campo é envolvido por aspas duplas `"`, sendo que o que se encontra dentro delas deve ser considerado como um campo só!


A saída dos arquivos deve ser no mesmo formato que as entradas.


### 3.1 Dados disponíveis

Dentro do diretório `data/` encontram-se três arquivos. `filmes-pequeno.csv` e `usuarios.csv` são arquivos gerados à mão, enquando `filmes-grande.csv` é um arquivo com quase 1000 filmes retirados da base de dados https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset apenas com os campos explicitados. 

## 4. Compilação e execução

O arquivo `Makefile` compila e gera o executável `tp1`. Na compilação ele procura arquivos cabeçalhos na pasta `include`, códigos fonte em `src` e o arquivo que contém a função main em `client`. 



Ao executar `make`, modifique a variável `CLI` para mudar o arquivo cliente. Por exemplo,

    make CLI=client/main2.c

utilizaria a função main do arquivo `client/main2.c`. Por padrão, o makefile usa o arquivo `client/main.c`.

Para rodar o trabalho, execute o comando

    ./tp1


A pasta `.vscode` contém uma configuração básica para permitir debugar e rodar no vscode (apenas para todos os arquivos na mesma pasta).

## 5. Regras Gerais

O trabalho deverá ser feito **em dupla** e pelos próprios alunos, isto é, os alunos deverão necessariamente conhecer e dominar todos os trechos de código criados. 

Cada dupla deverá trabalhar independente das outras, não sendo permitido a cópia ou compartilhamento de código. O professor irá fazer verificação automática de plágio. Trabalhos identificados como iguais, em termos de programação, serão penalizados com a nota zero. Isso também inclui a dupla que forneceu o trabalho, sendo, portanto, de sua obrigação a proteção de seu trabalho contra cópias ilícitas. 

## 6. Entrega do Trabalho

O trabalho deverá ser submetido pelo Repl.it  e também pelo AVA até  as 23:59 do dia 11/04/2021. 

O arquivo enviado pelo AVA deve  seguir o padrão: TEP-2021_MATRICULA1_MATRICULA2.zip, substituindo a matrícula pelos respectivos números de matrícula da dupla.  
O arquivo zip deve conter:
Todos os arquivos necessários para compilação (cabeçalhos e códigos fontes)
`Makefile` que compile o programa corretamente em um ambiente Linux.
`README.md` contendo nome da dupla e com considerações de projeto que julgue necessário, incluindo as decisões de projeto tomadas. Por exemplo, explicação breve das bibliotecas,  etc.
 
O código fonte deverá estar bem comentado, isto é, todas os structs e funções devem ter descrições claras do que ela faz, o que representa cada parâmetro e o que ela retorna (se houver).  Pode-se adicionar também comentários que ajude a entender a lógica da  questão.

## 7. Avaliação

O trabalho será corrigido em dois turnos: correção do professor e entrevista. A correção do professor (CP) gerará uma nota entre 0 e 10 e as entrevistas (E) serão realizadas posteriormente à data de entrega do trabalho e será atribuída uma nota entre 0 e 1. Alunos que fizeram o trabalho em dupla farão a entrevista juntos porém terão seus desempenhos na entrevista avaliados de forma individual. Pequenas e pontuais correções de código serão permitidas no momento da entrevista, o que poderá acarretar em uma CP maior.

A nota final (NF) do trabalho será dada pela seguinte fórmula: NF = E * CP

O trabalho será pontuado de acordo com sua funcionalidade e outros aspectos de implementação, conforme as listas abaixo.

#### Aspectos funcionais

1. Inicialização. Capacidade de carregar os arquivos usando estruturas dinâmicas. (5%)
2. Cadastrar e persistir  usuários. Isto é, ao cadastrar um usuário e sair do programa, este usuário é salvo no arquivo usuarios.csv e pode fazer o login na próxima vez. (10%)
3. Listar filmes com paginação. (5+15=20%)
3.1 Mostrar os metadados do filme
3.2 Assitir filmes e atribuir uma data/nota;
4. Pesquisar de filmes, indicando filmes com nomes similares. (10%)
5. Exibir o histórico ordenado por nota, decrescente;(10%)
6. Exibir o histórico ordenado por data, decrescente; (10%)
7. Excluir conta (5%)

#### Aspectos de desenvolvimento:

1. Uso correto de TADs para abstração dos elementos envolvidos no trabalho. Menos *main* mais TADs! (20%)
2. Executar o programa com o valgrind, sair corretamente e não ter vazamento de memória. (20%) 

## 8. Funcionalidades extras

As funcionalidades aqui não são completamente suportadas pelo sistema, mas são simples de implementar:

### Admin

Pode existir um usuário admin que tem o poder de manipular o sistema com mais liberdade. O seu único diferencial é seu nome, que é `admin`. Ele poderá adicionar e excluir filmes do catálogo. Os filmes não precisam ser excluídos, mas apenas marcados como inativos.

