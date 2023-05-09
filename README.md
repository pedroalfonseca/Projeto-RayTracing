# Projeto Ray-tracing
Implementação do algoritmo de renderização *Ray-tracing*. Para gerar o arquivo PNG da imagem, basta rodar o [script de geração de imagem](gen_image.py) com os argumentos referentes à configuração desejada:

```shell
python3 gen_image.py <opção de compilação> <opção de cena>
```

### Opções de compilação
- Sem otimizações, com avisos (safe): `-s`
- Com otimizações, sem avisos (fast): `-f`

### Opções de cena
- Amostra com todas as features do projeto (sample): `-s`
- Estético e com um "aspecto de sonho" (dreamy): `-d`
- Lê a cena descrita no [arquivo de entrada](in.txt) (custom): `-c`