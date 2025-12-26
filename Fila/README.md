# Jogo de Fila (Cartas)

Este projeto é um jogo simples em C que simula uma fila de cartas, permitindo ao usuário comprar (enfileirar) e descartar (desenfileirar) cartas, além de visualizar o estado atual da fila.

## Como funciona
- **Comprar carta:** Adiciona uma nova carta ao final da fila.
- **Descartar carta do topo:** Remove a carta que está no início da fila (primeira a entrar, primeira a sair).
- **Mostrar fila:** Exibe todas as cartas presentes na fila, na ordem em que foram compradas.
- **Sair:** Encerra o programa e limpa a fila.

## Como executar
1. **Abra o terminal e navegue até a pasta do projeto:**
   ```sh
   cd Fila
   ```
2. **Compile o programa:**
   ```sh
   gcc main.c -o main
   ```
3. **Execute o programa:**
   ```sh
   ./main
   ```

## Exemplo de uso
```
Jogo de Cartas: Compra e Descarte (Fila)

1. Comprar carta
2. Descartar carta do topo
3. Mostrar fila
0. Sair
Escolha: 1
Nome da carta: Ás de Copas
Escolha: 1
Nome da carta: Rei de Espadas
Escolha: 3
Cartas na fila: [Ás de Copas] [Rei de Espadas]
Escolha: 2
Carta 'Ás de Copas' removida do topo da fila.
Escolha: 3
Cartas na fila: [Rei de Espadas]
```

## Observações
- O programa não salva os dados após ser fechado.
- A fila segue a lógica FIFO (First In, First Out).

---
Desenvolvido por João Victor, Otávio Augusto e Yuri Elias.
