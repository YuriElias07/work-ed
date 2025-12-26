# Jogo de Árvore Genealógica

Este projeto é um jogo interativo em C para criar e visualizar uma árvore genealógica simples pelo terminal. Você pode adicionar pessoas, definir relações de pai/mãe e filhos, e visualizar a estrutura da família em formato de árvore.

## Como funciona
- **Adicionar pessoa (sem pais):** Cria a raiz da árvore genealógica (primeira pessoa).
- **Adicionar filho:** Adiciona um novo membro como filho de um pai, mãe ou ambos já cadastrados.
- **Mostrar árvore:** Exibe a árvore genealógica formatada, mostrando as relações familiares.
- **Sair:** Encerra o programa.

## Como executar
1. **Abra o terminal e navegue até a pasta do projeto:**
   ```sh
   cd Arvore
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
Árvore Genealógica

1. Adicionar pessoa (sem pais)
2. Adicionar filho
3. Mostrar árvore
0. Sair
Escolha: 1
Nome da pessoa: João
Pessoa 'João' adicionada como raiz.

Escolha: 2
Nome do filho: Maria
Nome do pai (ou deixe vazio): João
Nome da mãe (ou deixe vazio):
Filho 'Maria' adicionado.

Escolha: 3
Árvore Genealógica:
- João
  - Maria
```

## Observações
- Só é possível adicionar uma raiz (primeira pessoa).
- Para adicionar filhos, o pai ou a mãe já devem existir na árvore.
- O programa não salva os dados após ser fechado.

---
Desenvolvido por João Victor, Otávio Augusto e Yuri Elias.
