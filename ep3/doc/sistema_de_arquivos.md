## Divisão de blocos

- 38 blocos -> tabela de blocos
- 1 bloco  -> bitmap (ou 3 se tivermos que gravar como texto)
- 25567 blocos -> diretórios e arquivos (ou 25568 pelo mesmo motivo acima)

## Tabela de blocos

cada 6 bytes representa um bloco. A posição dos bytes é o indice dos blocos e os 6 bytes são a string que contém o valor numérico do próximo bloco do arquivo. A tabela da figura 5-9 do livro ficaria assim (sem as queebras de linha e os índices):

0. xxxxxx
1. xxxxxx
2. "00010"
3. "00011"
4. "00007"
5. xxxxxx
6. "00003"
7. "00002"
8. xxxxxx
9. xxxxxx
10. "00012"
11. "00014"
12. "00000"
13. xxxxxx
14. "00000"
15. xxxxxx

Os xxxxxx podem ser qualquer caractere, e "00000" representa o fim do arquivo. As strings só podem ter 5 caracteres pois o ultimo é o nulo ('\0') que indica o fim da string.

## Bitmap

A ideia é guardar essas informações em bytes mesmo, com um bit por arquivo. Mas se não der (Por problemas de implementação) podemos gravar com 3 caracteres para representar 8 arquivos, passando um número de até 3 algarismos para a base 2.
