# aes256
Implementation of Advanced Encrypting standart

### Benchmarks

|      Standart    |     1 MB    |    10 MB    |   100 MB    |       1 GB        |
|       :---:      |    :----:   |     :---:   |     :--:    |       :---:       | 
|      AES-128     |   0m0.781s  |   0m8.240s  |  0m56.165s  |      8m20.114s    |
|      AES-192     |   0m1.011s  |   0m10.945s |  1m29.946s  |      9m2.488s     |
|      AES-256     |   0m0.963s  |   0m9.352s  |  1m30.978s  |      9m6.243s     |


### Compiling


```
git clone https://github.com/yhetman/aes256
cd aes256
make
```

To reocompile the code use:

```
make re
```

### Usage

```
./aes ./path_to_input_file
```

### Available standarts

|       Name       |  Key size | Number of Rounds  |
|       :---:      |    :--:   |       :---:       | 
|      AES-128     |    128    |        10         |
|      AES-192     |    192    |        12         |
|      AES-256     |    256    |        14         |


