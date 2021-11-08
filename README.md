# AES 128 192 256

---

Implementation of Advanced Encrypting Standart in pure C.


### Available standarts

|       Name       |  Key size | Number of Rounds  |
|       :---:      |    :--:   |       :---:       | 
|      AES-128     |    128    |        10         |
|      AES-192     |    192    |        12         |
|      AES-256     |    256    |        14         |



### Benchmarks for AES as block cipher

|      Standart    |     1 MB    |    10 MB    |   100 MB    |       1 GB        |
|       :---:      |    :----:   |     :---:   |     :--:    |       :---:       | 
|      AES-128     |   0m0.311s  |   0m2.833s  |  0m28.657s  |      7m24.910s    |
|      AES-192     |   0m0.291s  |   0m2.796s  |  0m28.343s  |      7m43.737s    |
|      AES-256     |   0m0.343s  |   0m2.877s  |  0m28.450s  |      7m36.052s    |


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
./aes -i ./input_file -o ./output_file -s {16 | 24 | 32} -k ./key_file -m {1 | 2 | 3 | 4 | 5}
```

### Options and flags

```

Flags:
	-i  -- specify ./path/to/input/file
	-o  -- specify ./path/to/output/file
	-k  -- specify ./path/to/key/file
	-s	-- specify the key length in bytes.
	-e	-- specify the encrypting process.
	-d	-- specify the decrypting process.
	-m	-- specify stream mode of AES.

Available stream modes:
		1 -- ECB;
		2 -- CBC;
		3 -- CFB;
		4 -- OFB;
		5 -- CTR

```

### Benchmarks for AES-256 stream modes

|   Mode    |     1 MB    |    10 MB    |   100 MB    |
|   :---:   |    :----:   |     :---:   |     :--:    | 
|    ECB    |   0m0.030s  |   0m0.069s  |  0m0.500s   |
|    CBC    |   0m0.186s  |   0m1.652s  |  0m16.648s  |
|    CFB    |   0m0.201s  |   0m1.641s  |  0m16.333s  |
|    OFB    |   0m0.187s  |   0m1.671s  |  0m17.022s  |
|    CTR    |   0m0.189s  |   0m1.662s  |  0m19.935s  |
