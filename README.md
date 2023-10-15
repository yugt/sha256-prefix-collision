# sha256-prefix-collision
This project is intended to find SHA256 prefix collisions.
For example,

```python
from hashlib import sha256

>>> sha256("08RTz8".encode()).hexdigest()
8531fd370c9984774c4ee4f1f16683e9c2195e8772faad007ac2c9ce4c7795d2
>>> sha256("4iRDWF".encode()).hexdigest()
8531fd370c9984779b602881d81a89244292f23a0b06c0c0e128b9169c08a6e5
```

Notice that the first 16 heximal digests are the same, creating a partial collision (1/4 of full length).

Current code works on all input strings of length 6 with character set {0-9, A-Z, a-z},
so there are 62^6 plaintexts to hash and check if there is a collision.
70 prefix collisions of length >= 16 heximal digits (64 bits) are found among them.

| str1 | str2 | sha256 prefix  |
|------|------|----------------|
|`08RTz8`|`4iRDWF`|`8531fd370c998477`|
|`0SG0Z5`|`UH1so8`|`35bdd7271cabcdec`|
|`0sWAwh`|`ohvTbh`|`048b4622dd70d7eb`|
|`18Xdvr`|`BDfqWl`|`b6708b8d586ee66d`|
|`12IqLF`|`ZllZFU`|`ac7b6be62254956c`|
|`1c1ovK`|`d2AEDs`|`2df1b52747849787`|
|`1km1H4`|`xfAVrO`|`2bd3e41095a1e099`|
|`2iqe8N`|`Es7KO3`|`4ccc0921312bbae5`|
|`3ncLKE`|`bzFrVW`|`6d19403a6046ed0b`|
|`4bzmKq`|`BtT7JV`|`5083bde7a551b78b`|
|`4GZqwN`|`IZKFi4`|`b41677adae347fd4`|
|`51nw9e`|`XUmeqA`|`9ed9e215ebdc28f6`|
|`5rOkL7`|`wpqa8I`|`6d3456e32ae030b9`|
|`6MNZnx`|`hzF9e9`|`104aa1c8b36292c2`|
|`6H1vFI`|`tcwynX`|`3e5db9fa3ef0c3c9`|
|`75FRLP`|`MrFsSR`|`ded30dd96861f052`|
|`97aNk4`|`Z8EiIZ`|`82918990ffd2df0d`|
|`9zReHs`|`Zsz6G0`|`51485812a0d636a8`|
|`9qprc7`|`fc6qso`|`218536a553be88f3`|
|`93BZem`|`rxZKCE`|`9cb2c87555abc1c6`|
|`An8itH`|`IVKS5g`|`c8f28b7db7823f98`|
|`AZTHUy`|`ilsjpc`|`36a167b61ede94a2`|
|`BpmepV`|`N0ULpv`|`d46c91709ec5d6aa`|
|`CMi73M`|`eXMbB2`|`7aee801bc5841333`|
|`FuWZbV`|`cs7TvW`|`38dc2370adf1049e`|
|`FcVanX`|`o81jgh`|`7c6aea01885634ca`|
|`G78reA`|`ucZi2L`|`55217914496b123c`|
|`Hbd48m`|`LBGrma`|`8899ac3ab00b0447`|
|`H4aLym`|`Xh9zs3`|`0211641d72a8026f`|
|`Hmv8VN`|`c3Y5gl`|`6f7db272d4b4ed64`|
|`Hp2PRi`|`ns8vX7`|`623ad6f9cabfa189`|
|`IHk2Kq`|`Lg05bl`|`66323e97096d5f3f`|
|`Ien78k`|`mR5h1f`|`9817bcbc75a13aba`|
|`Jtt6z3`|`RAteIQ`|`ef6e39f9888e322a`|
|`JGBM1n`|`jEqXmC`|`485cfffa75c35e3c`|
|`J8tyBp`|`q9eIvh`|`97a16a8821cfecbd`|
|`JvKxRs`|`qmJ0Pl`|`0c08e9cdd1fa749c`|
|`LBTbrO`|`M1iqkU`|`f3b6afd60bb759e4`|
|`LCk1Th`|`wpgDBs`|`3e5166f98aecddf8`|
|`N48qSn`|`Pcnza9`|`342ef31974cf4231`|
|`Ppnn7y`|`XGLAPk`|`32e7f9c87a6f21b2`|
|`Pd3Z4z`|`oqOYr2`|`11e12204d6cbd249`|
|`Q8d1zO`|`blA5UJ`|`cc8271a184bc88c7`|
|`SU1aKn`|`XDVEUm`|`d770de591fd79060`|
|`SyK5VM`|`k0Fqyg`|`48a868ad7adf37f0`|
|`TmN067`|`olIJFL`|`b56e135549bb7bb6`|
|`TFfJrG`|`onnEl5`|`5faaac831ae96b3e`|
|`VL32W8`|`g6KK9y`|`d86d26e9ceaf3c4f`|
|`VV65zA`|`oVIEvK`|`8e71454a0de65c07`|
|`VxGKXU`|`z32JZx`|`e9325453873b68ca`|
|`WSwnSj`|`zsnyOd`|`34444f45121a93a8`|
|`XcqL73`|`jfRvkg`|`1a8a99e094c52d1d`|
|`Y6yl6c`|`pUCuFQ`|`3dd7129a3ff1c702`|
|`Zj8gIC`|`kFzhuA`|`5d2656a01e218a6f`|
|`ZJcEoN`|`ytA6YQ`|`55aa05f4405d9fd8`|
|`aj21xD`|`eKjBs6`|`b3fc09d6f4379d64`|
|`aXG1Ln`|`fhjA2p`|`383e9035acf80a22`|
|`b2KVvV`|`eQa3xX`|`22dabd5b5bdd135b`|
|`cyeRq6`|`pHuzS8`|`4d015089ce5280ad`|
|`enYfbA`|`g3Lyzz`|`9c21700ec428d62b`|
|`fF0zyZ`|`lAwvYq`|`cc7a3310e735dc54`|
|`goeFmG`|`nZLTMx`|`f443d0f37c521588`|
|`gqAtQJ`|`yzcfxj`|`1486b90295cc75b9`|
|`iJCPvo`|`yWlGz8`|`9546b9307a96ee75`|
|`nbVd8S`|`o8kpMI`|`05f7cd501e65b8c7`|
|`p0AxwS`|`r1W1Lz`|`ca7e13c23c3984f1`|
|`pOaOXY`|`vrcu8Z`|`22898d29b3b336c7`|
|`pxQPUL`|`zO3htV`|`7b5fcf0130ae9e29`|
|`rBmx5t`|`w2EJd7`|`6918675a73de7b0b`|
|`u40AZT`|`wMs6I3`|`ff80d0cb4162390b`|
