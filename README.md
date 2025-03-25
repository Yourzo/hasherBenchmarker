# Hasher benchmarker

is simple tool, built in C++, to measures and compare speeds of hashing functions in 
unordered map. Currently, it supports key types: int, std::string and pointer.
It was built as a part of my bachelor's thesis.

## Bachelor's thesis:

### Comparison of hash function implementations for hash tables

## Setup
* Start the program from correct directory with config.json.
* Results can be found in results directory that gets created after first run.



## Config.json
Application can do multiple benchmarks each run.
Every benchmark produces one result a pair of data and metadata files.
1. Define how many replications will be executed for each test (these will stay the same across all benchmarks)

```
"replications": 40,
```
2. Define `benchmarks` field, (it's field of fields).
3. In every benchmark define your test for given benchmark.
4. Shuffle option can be added (default is false).

```json
{
    "replications": 40,
    "shuffle": true,
    "benchmarks": [
        [
            {
                "here": "define test"
            }
        ]
    ]
}
```
<h2>TEST:</h2>
<h4>NAME:</h4>
Choose name, this will be used as name of the column in ```result/.data.csv```:

```json
"name": "basic int 10 000 jenkins 32 bit"
```
<h4>HASHER:</h4>
Next hasher has to picked, hasher works as a key type identification too:

```json
"hasher": "jenkins 32 bit"
```

```int``` hashers:

| name                                                                                                                                               |
|----------------------------------------------------------------------------------------------------------------------------------------------------|
| [**hash 1**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L13)              |
| [**jenkins 32 bit**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L28)      |
| [**multiplication hash**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L45) |
| [**indentity_int**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L58)       |
| [**std::hash int**](https://en.cppreference.com/w/cpp/utility/hash)                                                                                |
| [**murmur2_int**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L64)         |
| [**murmur3_int**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/int_hashers.hpp#L71)         |

```std::string``` hashers:

| name                                                                                                                                           |
|------------------------------------------------------------------------------------------------------------------------------------------------|
| [**rolling hash**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/string_hashers.hpp#L9)  |
| [**jenkins hash**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/string_hashers.hpp#L22) |
| [**std::hash string**](https://en.cppreference.com/w/cpp/utility/hash)                                                                         |
| [**djb2**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/string_hashers.hpp#L32)         |                                                                                                                                 
| [**sdbm**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/string_hashers.hpp#L42)         |
| [**murmur2_str**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/string_hashers.hpp#L52)  |
| [**murmur3_str**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/string_hashers.hpp#L59)  |                                                                                                                            |

pointer hashers:

| name                                                                                                                                                       |
|------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [**shift 3 pointer align 8**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/pointer_hasher.hpp#L16)  |
| [**shift 4 pointer align 16**](https://github.com/Yourzo/hasherBenchmarker/blob/d55ddf272bdb4322f62118f44df11f8fc195824b/hasherLib/pointer_hasher.hpp#L16) |
| [**shift 5 pointer align 32**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/pointer_hasher.hpp#L16) |
| [**murmur2_ptr**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/pointer_hasher.hpp#L36)              |
| [**murmur3_ptr**](https://github.com/Yourzo/hasherBenchmarker/blob/2eff7ee3beb9cc8e3677f680173c9cd8eacd7737/hasherLib/pointer_hasher.hpp#L44)              |
| [**std::hash ptr**](https://en.cppreference.com/w/cpp/utility/hash)                                                                                        |

<h4>Generators</h4>
In next line key generator is defined, generator type has to match key type. Generators are heavily reliant on [**random**](https://en.cppreference.com/w/cpp/header/random) from c++ standard library.

```json
"generator": "basic int"
```

```int``` generators:

| name                |
|---------------------|
| [**basic int**]()   |
| [**normal dist int**]() |

```std::string``` generators:

| name                         |
|------------------------------|
| [**long string**]()          |
| [**small string**]()         |
| [**random length string**]() |
pointer generators:

| name                   |
|------------------------|
| [**packed pointer**]() |
| [**random pointer**]() |

<h4>Size of the map</h4>
Last field requires us to define how many elements are to be in tested map.

```json
"mapSize":10000,
```

<h3>Config examples:</h3>
* Config with one test:

```json
{
    "replications": 40,
    "benchmarks": [
        [
            {
                "name": "basic int 10 000 jenkins 32 bit",
                "hasher": "jenkins 32 bit",
                "generator": "basic int",
                "mapSize": 10000
            }
        ]
    ]
}
```
* 
* Config with two tests, each in one benchmark:

```json
{
    "replications": 40,
    "benchmarks": [
        [
            {
                "name": "basic int 10 000 jenkins 32 bit",
                "hasher": "jenkins 32 bit",
                "generator": "basic int",
                "mapSize": 10000
            },
            {
                "name": "basic int 10 000 jenkins 32 bit",
                "hasher": "jenkins 32 bit",
                "generator": "basic int",
                "mapSize": 10000
            }
        ]
    ]
}
```
* Config with multiple benchmarks:

```json
{
    "replications": 40,
    "benchmarks": [
        [
            {
                "name": "basic int 10 000 jenkins 32 bit",
                "hasher": "jenkins 32 bit",
                "generator": "basic int",
                "mapSize": 10000
            }
        ],
        [
            {
                "name": "packed pointer 1000 shift 4",
                "hasher": "shift 4 pointer",
                "generator": "packed pointer",
                "mapSize": 1000000
            }
        ]
    ]
}
```

###### Coming soon:
* finishing this file (documentation)
* Python script to process the results.
