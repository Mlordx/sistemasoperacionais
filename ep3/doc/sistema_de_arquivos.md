## Divisão de blocos

- 32 blocos -> tabela de blocos
- 1 bloco  -> bitmap (ou 3 se tivermos que gravar como texto)
- 25567 blocos -> diretórios e arquivos (ou 25568 pelo mesmo motivo acima)

## Tabela de blocos

cada 5 bytes representa um bloco. A posição dos bytes é o indice dos blocos e os 5 bytes são caracteres que contém o valor numérico do próximo bloco do arquivo. A tabela da figura 5-9 do livro ficaria assim (sem as queebras de linha e os índices):

0. xxxxx
1. xxxxx
2. 00010
3. 00011
4. 00007
5. xxxxx
6. 00003
7. 00002
8. xxxxx
9. xxxxx
10. 00012
11. 00014
12. 00000
13. xxxxx
14. 00000
15. xxxxx

Os "xxxxx" podem ser qualquer caractere, e "00000" representa o fim do arquivo.

## Bitmap

A ideia é guardar essas informações em bytes mesmo, com um bit por arquivo. Mas se não der (Por problemas de implementação) podemos gravar com 3 caracteres para representar 8 arquivos, passando um número de até 3 algarismos para a base 2.
