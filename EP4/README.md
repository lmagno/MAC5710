## EP4
**Lucas Magno**  
**7994983**

#### Utilização
Para compilar o programa, basta executar o comando `make` e um executável chamado `EP4` será criado.

Para rodar o programa, basta chamá-lo com dois argumentos: o valor para a penalidade do *gap* e o caminho para algum arquivo FASTA definindo duas sequências de aminoácidos, como o exemplo a seguir.

#### Arquivo FASTA
*Insulina.txt*   
```
>AAA59172.1 insulin [Homo sapiens]
MALWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGG
GPGAGSLQPLALEGSLQKRGIVEQCCTSICSLYQLENYCN

>AAA19033.1 insulin [Oryctolagus cuniculus]
MASLAALLPLLALLVLCRLDPAQAFVNQHLCGSHLVEALYLVCGERGFFYTPKSRREVEELQVGQAELGG
GPGAGGLQPSALELALQKRGIVEQCCTSICSLYQLENYCN
```

#### Exemplo de saída
Dada a entrada

`./EP4 -2 Exemplos/Insulina.txt`

obtemos a saída

```
Strings:
  MALWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALEGSLQKRGIVEQCCTSICSLYQLENYCN

  MASLAALLPLLALLVLCRLDPAQAFVNQHLCGSHLVEALYLVCGERGFFYTPKSRREVEELQVGQAELGGGPGAGGLQPSALELALQKRGIVEQCCTSICSLYQLENYCN

Matches:
       **        * ***   *                              *   * *     *         *   *     *                         
  MA-LWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALE-GSLQKRGIVEQCCTSICSLYQLENYCN
  || |   |||||||| |   ||| |||||||||||||||||||||||||||||| ||| | ||||| ||||||||| ||| |||   |||||||||||||||||||||||||
  MASL-AALLPLLALLVLCRLDPAQAFVNQHLCGSHLVEALYLVCGERGFFYTPKSRREVEELQVGQAELGGGPGAGGLQPSALEL-ALQKRGIVEQCCTSICSLYQLENYCN

       **        * ***   *                              *   * *     *         *   *     *                         
  MA-LWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALEG-SLQKRGIVEQCCTSICSLYQLENYCN
  || |   |||||||| |   ||| |||||||||||||||||||||||||||||| ||| | ||||| ||||||||| ||| |||   |||||||||||||||||||||||||
  MASL-AALLPLLALLVLCRLDPAQAFVNQHLCGSHLVEALYLVCGERGFFYTPKSRREVEELQVGQAELGGGPGAGGLQPSALE-LALQKRGIVEQCCTSICSLYQLENYCN

       **        * ***   *                              *   * *     *         *   *   **                         
  MA-LWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALEGSLQKRGIVEQCCTSICSLYQLENYCN
  || |   |||||||| |   ||| |||||||||||||||||||||||||||||| ||| | ||||| ||||||||| ||| |||  |||||||||||||||||||||||||
  MASL-AALLPLLALLVLCRLDPAQAFVNQHLCGSHLVEALYLVCGERGFFYTPKSRREVEELQVGQAELGGGPGAGGLQPSALELALQKRGIVEQCCTSICSLYQLENYCN

Score: 483
Number of alignments found: 3
```
