# EP3
Este programa realiza a compactação e a descompactação de arquivos através da codificação de Huffman, como visto em aula.

Para compilá-lo basta executar o comando `make` e seu uso se dá em dois formatos:

* Compactação:

    `> ./EP3 c input output`

* Descompactação:

    `> ./EP3 d input output`

Cujas saídas são (exemplos rodados no prório executável):

* Compactação:
    ```
    Compressing 'EP3' to 'EP3.out'...

    Size of original file:   53544
    Size of compressed file: 31726
    Compression: 59.3%
    ```
* Descompactação:
    ```
    Decompressing 'EP3.out' to 'EP3_2'...
    ```

E vale observar que o executável `EP3_2` é idêntico ao `EP3` original. :)
