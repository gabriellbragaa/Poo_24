# Porta minas de um grafite só

<!-- toch -->
[Intro](#intro) | [Orientações por linguagem](#orientações-por-linguagem) | [Guide](#guide) | [Shell](#shell) | [Draft](#draft)
-- | -- | -- | -- | --
<!-- toch -->

![cover](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/grafite/cover.jpg)

Faça o modelo de uma lapiseira que pode conter um único grafite.

[![explicação](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/grafite/../../wiki/images/explicacao.png)](https://youtu.be/LvZODN2rL6s)

***

## Intro

O objetivo dessa atividade é implementar uma lapiseira que permite inserir, remover grafite e escrever em uma folha, considerando a dureza e tamanho do grafite.

- Descrição
  - A lapiseira é capaz de iniciar, inserir e remover grafite, além de escrever em uma folha.
  - Para inserir um grafite, é necessário especificar o calibre (float), a dureza (string) e o tamanho em mm (int).
  - A remoção do grafite só é possível se houver algum na lapiseira.
  - A escrita na folha só é possível se houver grafite suficiente e se o tamanho do grafite for superior a 10mm.
  - A quantidade de grafite gasto varia de acordo com a dureza do grafite. Quanto mais macio, mais ele se desgasta.
  - Quando o tamanho do grafite atinge 10mm, não é mais possível escrever.
  - Se não houver grafite suficiente para terminar a escrita na folha, é emitido um aviso de texto incompleto.

- Responsabilidades
  - A classe `Lead` é responsável por armazenar as informações do grafite.
    - `thickness` é a espessura e terá valores como 0.3, 0.5, 0.7.
    - `hardness` é a dureza e poderá ter os seguintes valores: `HB, 2B, 4B, 6B`.
    - O método `usagePerSheet` retorna a quantidade de grafite gasto por folha.
      - Um grafite `HB` gasta `1mm` por folha.
      - Um grafite `2B` gasta `2mm` por folha.
      - Um grafite `4B` gasta `4mm` por folha.
      - Um grafite `6B` gasta `6mm` por folha.
    - `size` representa o tamanho do grafite em `milímetros`.
  - A classe `Pencil` é responsável por gerenciar as operações de inserção, remoção de grafite e escrita na folha.
    - Ela referencia um único objeto lapiseira como atributo.
    - E também possui um indicador de espessura `thickness`.
  - A class `Adapter` faz a integração entre as chamadas de teste e as classes `Lead` e `Pencil`.
    - Um método de atenção especial é o `insert`. Nele o `Adapter` recebe os dados do `Lead`.
    - Ela deve criar o objeto `Lead` e passá-lo à lapiseira que ela gerencia.

```ts
//Adapter
void insert(thickness: float, hardness: str, size: int) {
    this.pencil.insert(new Lead(thickness, hardness, size));
}

```

- Comandos
  - Todos os comandos seguem o modelo `$comando arg1 arg2 ...`.
  - `$iniciar calibre` - Inicializa a lapiseira com um determinado calibre.
  - `$inserir calibre dureza tamanho` - Insere um grafite com o calibre, dureza e tamanho especificados.
    - erros:
      - `fail: calibre incompativel` - Se o calibre do grafite for diferente do calibre da lapiseira.
      - `fail: ja existe grafite` - Se já houver um grafite na lapiseira.
  - `$remover` - Remove o grafite da lapiseira, se houver.
    - erros:
      - `fail: nao existe grafite` - Se não houver grafite na lapiseira.
  - `$escrever` - Escreve na folha, considerando o grafite presente na lapiseira.
    - O grafite é gasto de acordo com a dureza.
    - erros:
      - `fail: nao existe grafite` - Se não houver grafite na lapiseira.
      - `fail: tamanho insuficiente` - Se o tamanho do grafite for insuficiente para começar a escrita.
      - `fail: folha incompleta` - Se o grafite não for suficiente para terminar a escrita.

## Orientações por linguagem

- Cada linguagem tem suas formas de definir ausência de valor.
- Por exemplo, vamos criar uma variável que pode ser um inteiro ou não ter valor.

- Python
  - `None` é o valor padrão para ausência de valor.
  - `variavel: int | None = None` - Define uma variável que pode ser `int` ou `None`.
  - `variavel = 5` - Define a variável com um valor inteiro.
  - Teste: `if variavel is not None:`
- Java
  - `null` é o valor padrão para ausência de valor.
  - Tipos primitivos não podem ser null.
  - Todos as referências a objetos podem ser null.
  - Referências não inicializadas são null.
  - `Integer variavel = null` - Define uma variável que pode ser `Integer` ou `null`.
  - `variavel = 5` - Define a variável com um valor inteiro.
  - Teste: `if (variavel != null) {`
- C++
  - `nullptr` é o valor padrão para ausência de valor.
  - Apenas ponteiros podem ser nullptr.
  - Valores estáticos não podem ser nullptr.
  - Opções de abordagem com ponteiros:
    - `int* variavel = nullptr` - Define um ponteiro que pode ser `int` ou `nullptr`.
    - `std::shared_ptr<int> variavel = nullptr` - Define um ponteiro que pode ser `int` ou `nullptr`.
    - `variavel = new int(5)` - Define a variável com um valor inteiro.
    - Teste: `if (variavel != nullptr) {`
  - Opções de abordagem estática utilizando wrapper(empacotador).
    - `std::optional<int> variavel = std::nullopt` - Define uma variável que pode ser `int` ou `std::nullopt`.
    - `variavel = 5` - Define a variável com um valor inteiro.
    - Teste: `if (variavel.has_value()) {`
- TypeScript
  - `null` e `undefined` são os valores padrão para ausência de valor.
  - `let variavel: number | null = null` - Define uma variável que pode ser `number` ou `null`.
  - `variavel = 5` - Define a variável com um valor inteiro.
  - Teste: `if (variavel !== null) {`

## Guide

![diagrama](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/grafite/diagrama.png)

- Parte 1: Inserir
  - Crie a classe `Grafite` com o atributo `size`.
  - Crie a classe `Lapiseira` com o atributo `tip` inicializado como `null`.
  - Implemente o método `hasGrafite` que retorna `true` se houver grafite na lapiseira.
  - Implemente o método `insert` que insere um grafite na lapiseira, se não houver grafite.
  - Implemente o método `toString` que mostra a lapiseira e o grafite presente.
  - Crie um objeto `lapiseira` e verifique se está vazia.
  - Crie um objeto `grafite` e insira na lapiseira.
  - Verifique se a lapiseira possui o grafite inserido.

- Parte 2: Remover Grafite
  - Implemente o método `remove` que retira o grafite da lapiseira, se houver.
  - Verifique se o grafite foi removido corretamente.
  - Verifique se o método `remove` retorna o grafite removido ou `null` se não havia grafite.

- Parte 3: Escrever na Folha
  - Implemente o método `writePage` que escreve na folha.
  - Implemente o método `usagePerSheet` que retorna a quantidade de grafite gasto por folha.
  - Verifique se a lapiseira consegue escrever na folha.
  - Faça as verificações antes de escrever na folha.
  - Para ver se o grafite será suficiente para escrever na folha, verifique qual o tamanho final que ele teria se fizesse a folha completa.
    - Se esse tamanho for menor que 10mm, ele deve gastar o que for possível e parar a folha pela metade.

***

## Shell

```bash

#TEST_CASE inserindo grafites

$init 0.5
$show
calibre: 0.5, grafite: null

#TEST_CASE incompativel

$insert 0.7 2B 50
fail: calibre incompativel
$insert 0.5 2B 50
$show
calibre: 0.5, grafite: [0.5:2B:50]
$end
```

***

```bash

#TEST_CASE inserindo

$init 0.3
$insert 0.3 2B 50
$show
calibre: 0.3, grafite: [0.3:2B:50]

#TEST_CASE ja existe

$insert 0.3 4B 70
fail: ja existe grafite
$show
calibre: 0.3, grafite: [0.3:2B:50]

#TEST_CASE removendo

$remove
$show
calibre: 0.3, grafite: null

#TEST_CASE reinserindo

$insert 0.3 4B 70
$show
calibre: 0.3, grafite: [0.3:4B:70]
$end
```

***

```bash

#TEST_CASE sem grafite

$init 0.9
$write
fail: nao existe grafite

#TEST_CASE escrevendo 1

$insert 0.9 4B 14
$write
$write
fail: tamanho insuficiente
$show
calibre: 0.9, grafite: [0.9:4B:10]
$end
```

***

```bash

#TEST_CASE escrevendo 2

$init 0.9
$insert 0.9 4B 16
$write
$show
calibre: 0.9, grafite: [0.9:4B:12]

#TEST_CASE escrevendo 3

$write
fail: folha incompleta
$show
calibre: 0.9, grafite: [0.9:4B:10]
$end
```

## Draft

<!-- links .cache/draft -->
- cpp
  - [fn.hpp](https://github.com/qxcodepoo/arcade/blob/master/base/grafite/.cache/draft/cpp/fn.hpp)
  - [shell.cpp](https://github.com/qxcodepoo/arcade/blob/master/base/grafite/.cache/draft/cpp/shell.cpp)
- java
  - [Shell.java](https://github.com/qxcodepoo/arcade/blob/master/base/grafite/.cache/draft/java/Shell.java)
- ts
  - [shell.ts](https://github.com/qxcodepoo/arcade/blob/master/base/grafite/.cache/draft/ts/shell.ts)
<!-- links -->
