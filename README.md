# Blackjack em C

Jogo de Blackjack (21) implementado em C, com suporte a múltiplos jogadores locais, apostas, split, double down e regras oficiais.

## Estrutura do projeto

- `src/` — código fonte (.c)  
- `include/` — headers (.h)  
- `build/` — arquivos objeto (.o), ignorados pelo git  
- `Makefile` — script para compilar  
- `README.md` — documentação do projeto  

## Como compilar

No terminal, rode:

```bash
make
````

O executável será criado na raiz do projeto com o nome `blackjack`.

## Como executar

```bash
./blackjack
```

## Limpar arquivos objeto e executável

```bash
make clean
```

## Requisitos

* GCC (compilador C)
* Make

## Jogo
<div style="display: flex; justify-content: space-between;">
  <div style="width: 100%">
    <img src="./images/menu.PNG" alt="menu do jogo">
    <img src="./images/regras.PNG" alt="regras do jogo">
  </div>
  <div style="width: 100%">
    <img src="./images/jogo.PNG" alt="imagem do jogo">
  </div>
</div>

## Autor

Gabriel — [GitHub](https://github.com/QTelesGabriel)
