# DP Week 2 - Task 1 - Building a Balatro-Like Run
Nama : Muhammmad Syifaul Qolbi
NRP  : 5224600072
Kelas: GT 12-C

# Balatro-Like Run — Core Loop, Invariant & Mutable (C++)

Simulasi game loop sederhana terinspirasi dari Balatro, ditulis dalam **C++17**. Program ini dirancang untuk memperlihatkan perbedaan antara **struktur yang tidak boleh berubah (invariant)** dan **bagian yang boleh dimodifikasi (mutable)** dalam sebuah sistem game berbasis antarmuka (interface).

---

## Cara Build dan Jalankan

### Persyaratan

- Compiler C++ yang mendukung **C++17** (g++, clang++, MSVC)
- Tidak memerlukan library eksternal

### Build dengan g++

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/RunSession.cpp src/SequentialInputGenerator.cpp src/RandomInputGenerator.cpp src/SimpleScoreRule.cpp src/SimpleRewardRule.cpp src/BonusRewardRule.cpp src/ShopSystem.cpp -o game
```

### Jalankan

```bash
./game.exe
```

---

## Struktur File

```
balatro/
├── include/
│   ├── TurnInput.h                  # Struct data input per ronde
│   ├── IInputGenerator.h            # Interface: generate input
│   ├── IScoringRule.h               # Interface: hitung base score
│   ├── IRewardRule.h                # Interface: hitung reward
│   ├── SequentialInputGenerator.h   # Implementasi: urutan tetap [3,5,7]
│   ├── RandomInputGenerator.h       # Implementasi: nilai acak 1–10
│   ├── SimpleScoreRule.h            # Implementasi: score = input
│   ├── SimpleRewardRule.h           # Implementasi: reward = baseScore
│   ├── BonusRewardRule.h            # Implementasi: reward berbeda tiap ronde
│   ├── ShopSystem.h                 # Fase toko
│   └── RunSession.h                 # Invariant — pengatur urutan fase
│
├── src/
│   ├── main.cpp                     # Entry point — tempat swap implementasi
│   ├── RunSession.cpp               # Implementasi game loop
│   ├── SequentialInputGenerator.cpp
│   ├── RandomInputGenerator.cpp
│   ├── SimpleScoreRule.cpp
│   ├── SimpleRewardRule.cpp
│   ├── BonusRewardRule.cpp
│   └── ShopSystem.cpp
│
└── README.md
```

| File | Peran |
|---|---|
| `RunSession` | **Invariant** — urutan 6 fase tidak boleh diubah |
| `IInputGenerator` / `IScoringRule` / `IRewardRule` | Interface abstrak — kontrak antar komponen |
| `SequentialInputGenerator` / `RandomInputGenerator` | **Mutable** — dapat diganti bebas |
| `SimpleScoreRule` | **Mutable** — logika skor bisa diubah |
| `SimpleRewardRule` / `BonusRewardRule` | **Mutable** — logika reward bisa diubah |
| `main.cpp` | Titik injeksi — pilih implementasi di sini |

---

## Urutan Fase (Invariant)

Urutan fase berikut didefinisikan di dalam `RunSession::run()` dan **tidak boleh diubah** dalam kondisi apapun:

```
1. Generate input       →  IInputGenerator::generate()
2. Compute base score   →  IScoringRule::compute()
3. Compute reward       →  IRewardRule::compute()
4. Update money         →  RunSession (satu-satunya tempat update money)
5. Shop phase           →  ShopSystem::offer()
6. Advance round        →  perulangan berlanjut ke ronde berikutnya
```

Urutan ini adalah **inti kontrak sistem**. Mengubah urutan ini sama dengan merusak arsitektur game.

---

## Contoh Output

```
=== RUN START ===

Round 1
[PLAY]   input generated: 1
[SCORE]  base score: 1
[REWARD] gain: 3 | money: 3
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   skipped (can afford, but chose to save)

Round 2
[PLAY]   input generated: 9
[SCORE]  base score: 9
[REWARD] gain: 18 | money: 21
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   skipped (can afford, but chose to save)

Round 3
[PLAY]   input generated: 2
[SCORE]  base score: 2
[REWARD] gain: 4 | money: 25
[SHOP]   offered: Bonus(+2) cost 2
[SHOP]   skipped (can afford, but chose to save)

=== RUN END ===
Final money: 25
```

Angka input berbeda setiap run karena `RandomInputGenerator` menggunakan `std::rand()`.

---

## Penjelasan Modifikasi

### Modifikasi 1 — Mengganti Input Generator

Di `main.cpp`, cukup ganti satu baris:

```cpp
// Sebelum (original):
SequentialInputGenerator inputGen;

// Sesudah (modifikasi):
RandomInputGenerator inputGen;
```

`RandomInputGenerator` menghasilkan nilai acak 1–10 menggunakan `std::rand()`, berbeda dari `SequentialInputGenerator` yang mengulang urutan tetap `{3, 5, 7}`.

**`RunSession` tidak disentuh sama sekali** — ia hanya memanggil `_inputGenerator->generate()` melalui pointer ke interface `IInputGenerator`.

---

### Modifikasi 2 — Mengubah Logika Reward

Di `main.cpp`, cukup ganti satu baris:

```cpp
// Sebelum (original):
SimpleRewardRule rewardRule;    // reward = baseScore

// Sesudah (modifikasi):
BonusRewardRule rewardRule;     // reward != baseScore
```

`BonusRewardRule` menerapkan logika berbeda per ronde:
- Ronde **ganjil**: `reward = baseScore + 2`
- Ronde **genap**: `reward = baseScore * 2`

**`RunSession` tidak disentuh sama sekali** — ia hanya memanggil `_rewardRule->compute(baseScore, round)` tanpa mengetahui formula di dalamnya.

---

## Refleksi

### Apa yang dimaksud dengan invariant dalam program ini?

Invariant dalam program ini adalah **urutan 6 fase dalam satu ronde**, yang didefinisikan di dalam `RunSession::run()`. Fase harus selalu berjalan dalam urutan: generate input → compute score → compute reward → update money → shop → advance round.

Urutan ini merupakan **kontrak struktural** game loop. Jika reward dihitung sebelum skor, atau money diupdate di luar fase reward, maka logika game menjadi tidak konsisten dan sulit diprediksi. Invariant bukan soal nilai atau angkanya, melainkan **jaminan urutan eksekusi** yang selalu dapat diandalkan di setiap ronde.

### Bagian mana yang bersifat mutable?

Bagian yang bersifat mutable adalah semua **implementasi konkret** yang diinjeksi ke dalam `RunSession` melalui pointer interface, yaitu:

- **`IInputGenerator`** — cara input dihasilkan (urutan tetap atau acak)
- **`IScoringRule`** — cara base score dihitung dari input
- **`IRewardRule`** — cara reward dihitung dari base score
- **`ShopSystem`** — tawaran apa yang muncul di toko

Semua bagian ini bisa diganti atau ditambah implementasi barunya tanpa menyentuh `RunSession` sama sekali. Cukup ganti objek yang diteruskan ke konstruktor `RunSession` di `main.cpp`.

### Ketika InputGenerator diganti, kenapa RunSession tidak ikut berubah?

Karena `RunSession` hanya bergantung pada **pointer ke interface** `IInputGenerator*`, bukan pada implementasi spesifiknya. Ia hanya tahu bahwa objek di balik pointer tersebut memiliki method `generate()` yang mengembalikan `TurnInput`. Apakah itu `SequentialInputGenerator` atau `RandomInputGenerator`, bagi `RunSession` tidak ada bedanya — kedua kelas tersebut memenuhi kontrak yang sama.

Ini adalah penerapan **Dependency Inversion Principle** dalam C++: `RunSession` (modul tingkat tinggi) tidak bergantung pada implementasi konkret (modul tingkat rendah), melainkan pada abstraksi (interface). Perubahan implementasi tidak memerlukan recompile atau modifikasi apapun pada `RunSession`.

### Apa yang terjadi jika logika scoring diletakkan di dalam RunSession?

Jika logika scoring diletakkan langsung di dalam `RunSession`, beberapa masalah serius akan muncul:

**Pertama**, `RunSession` akan melanggar *Single Responsibility Principle* — ia seharusnya hanya bertanggung jawab mengatur urutan fase, bukan menghitung skor. Mencampur dua tanggung jawab dalam satu kelas membuat kode sulit dipahami dan dipelihara.

**Kedua**, setiap kali ingin mengubah cara skor dihitung, developer harus masuk ke dalam `RunSession` dan mengubah kode di sana. Ini berbahaya karena `RunSession` adalah komponen inti — setiap perubahan berisiko merusak urutan fase secara tidak sengaja.

**Ketiga**, invariant terancam rusak. Begitu `RunSession` rutin diubah untuk alasan mutable (logika skor berubah), jaminan stabilitas urutan fase ikut goyah. Kode yang seharusnya stabil menjadi terus-menerus disentuh, dan kesalahan kecil bisa menggeser atau menduplikasi fase tanpa disadari.

Singkatnya: `RunSession` yang berubah setiap kali ada modifikasi perilaku adalah tanda bahwa arsitekturnya gagal memisahkan invariant dan mutable dengan benar.
