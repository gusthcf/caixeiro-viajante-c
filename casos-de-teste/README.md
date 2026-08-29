# Casos de teste

Cada caso é composto por um par de arquivos:

- `casoN.in`  — entrada a ser fornecida ao programa via `stdin`;
- `casoN.out` — saída esperada.

## Como executar

```bash
./exe < casos-de-teste/caso1.in
```

## Como comparar com a saída esperada

```bash
./exe < casos-de-teste/caso1.in | diff - casos-de-teste/caso1.out && echo "OK"
```

O `caso1` é o exemplo apresentado no enunciado do trabalho ([TP.pdf](../TP.pdf)).
