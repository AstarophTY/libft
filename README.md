<div align="center">

# 📚 libft

**Ma bibliothèque C standard maison — 42 School**

Réimplémentation propre des fonctions de la libc, étendue avec les
**listes chaînées**, **`get_next_line`** et **`ft_printf`**, le tout
réuni dans une seule archive `libft.a`.

![C](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Norm](https://img.shields.io/badge/norminette-passing-success)
![Build](https://img.shields.io/badge/build-make-blue)
![Standard](https://img.shields.io/badge/std-c89%2Fc99-lightgrey)

</div>

---

## 📖 Sommaire

- [Aperçu](#-aperçu)
- [Architecture](#-architecture)
- [Compilation](#-compilation)
- [Pipeline de build](#-pipeline-de-build)
- [Utilisation](#-utilisation)
- [Modules & fonctions](#-modules--fonctions)
- [Zoom : get_next_line multi-fd](#-zoom--get_next_line-multi-fd)
- [Zoom : ft_printf](#-zoom--ft_printf)
- [Norme](#-norme)

---

## 🔭 Aperçu

`libft` regroupe **50 fonctions** réparties en 7 modules. Tout est compilé
par un **unique `make`** (plus de règle `bonus` séparée) et produit l'archive
statique `libft.a` à lier dans tes projets.

| Caractéristique | Détail |
|---|---|
| 🧩 Modules | `ctype` · `mem` · `string` · `put` · `list` · `gnl` · `printf` |
| 📦 Sortie | `libft.a` |
| 🧾 Header | `includes/libft.h` (unique, tout est dedans) |
| 🎯 Flags | `-Wall -Wextra -Werror` |
| 🧠 GNL | multi-fd, stash **statique sans `malloc`** |
| ✅ Norme | norminette OK sur `srcs/` et `includes/` |

---

## 🏗 Architecture

```mermaid
graph TD
    A["libft.a"]:::lib

    subgraph SRC["srcs/"]
        C["ctype/<br/>isalpha · isdigit · isalnum<br/>isascii · isprint · toupper · tolower"]:::mod
        M["mem/<br/>memset · bzero · memcpy · memmove<br/>memchr · memcmp · calloc"]:::mod
        S["string/<br/>strlen · strlcpy · strlcat · strchr<br/>strrchr · strncmp · strnstr · strdup<br/>substr · strjoin · split · strtrim<br/>strmapi · striteri · atoi · itoa"]:::mod
        P["put/<br/>putchar_fd · putstr_fd<br/>putendl_fd · putnbr_fd"]:::mod
        L["list/<br/>lstnew · lstadd_front · lstadd_back<br/>lstsize · lstlast · lstdelone<br/>lstclear · lstiter · lstmap"]:::mod
        G["gnl/<br/>get_next_line"]:::mod
        F["printf/<br/>ft_printf · putchar · putstr<br/>puthex · putaddr · putnbr"]:::mod
    end

    H["includes/libft.h"]:::hdr

    C --> A
    M --> A
    S --> A
    P --> A
    L --> A
    G --> A
    F --> A
    H -.prototypes.-> SRC

    classDef lib fill:#00599C,stroke:#013a66,color:#fff,font-weight:bold;
    classDef mod fill:#1e293b,stroke:#475569,color:#e2e8f0;
    classDef hdr fill:#334155,stroke:#64748b,color:#fef08a;
```

**Dépendances internes** (qui appelle qui) :

```mermaid
graph LR
    calloc --> bzero --> memset
    strdup --> calloc
    strdup --> strlcpy
    substr --> calloc
    strjoin --> calloc
    split --> calloc
    split --> strlcpy
    itoa --> strdup
    strtrim --> substr & strchr
    gnl["get_next_line"] --> strchr & strdup & strjoin & strlcpy
    lstmap --> lstnew & lstadd_back & lstclear
    printf["ft_printf"] --> putchar & putstr & puthex & putnbr & putaddr
    putaddr --> puthex & putstr

    classDef d fill:#0f172a,stroke:#475569,color:#e2e8f0;
    class calloc,bzero,memset,strdup,strlcpy,substr,strjoin,split,itoa,strtrim,strchr,gnl,lstmap,lstnew,lstadd_back,lstclear,printf,putchar,putstr,puthex,putnbr,putaddr d;
```

---

## ⚙️ Compilation

```bash
make          # construit libft.a (libc + listes + gnl + printf)
make clean    # supprime les objets (.objs) et dépendances (.deps)
make fclean   # clean + supprime libft.a
make re       # fclean puis rebuild
make norm     # lance la norminette sur srcs/ et includes/
```

Le Makefile affiche une **barre de progression animée** pendant la compilation :

```text
libft [###############-----------]  58%  ft_atoi
 libft.a ready (50 objects)
```

---

## 🔧 Pipeline de build

```mermaid
flowchart LR
    subgraph dirs["arborescence srcs/*"]
        direction TB
        s1["*.c"]
    end
    s1 -->|"cc -Wall -Wextra -Werror<br/>-Iincludes -MMD -MP"| obj[".objs/*.o"]
    s1 -.->|"-MF"| dep[".deps/*.d"]
    obj -->|"ar rcs"| lib["libft.a"]
    dep -.->|"-include<br/>(rebuild incrémental)"| obj

    classDef a fill:#1e293b,stroke:#475569,color:#e2e8f0;
    classDef out fill:#00599C,stroke:#013a66,color:#fff;
    class s1,obj,dep a;
    class lib out;
```

- Les **objets** vont dans `.objs/`, les **dépendances** dans `.deps/`.
- `-MMD -MP` génère les `.d` : modifier un header ne recompile que le nécessaire.
- `VPATH` permet de garder les sources rangées par module tout en gardant des objets « à plat ».

---

## 🚀 Utilisation

Dans ton projet, lie l'archive et inclus le header :

```c
#include "libft.h"

int main(void)
{
    ft_printf("Hello %s, %d modules!\n", "world", 7);

    char **tokens = ft_split("a,b,c", ',');
    ft_printf("premier token: %s\n", tokens[0]);

    t_list *node = ft_lstnew(tokens[0]);
    ft_printf("taille liste: %d\n", ft_lstsize(node));
    return (0);
}
```

```bash
cc main.c -Iincludes -L. -lft -o app
# ou directement :
cc main.c libft.a -Iincludes -o app
```

---

## 🧩 Modules & fonctions

### `ctype` — classification de caractères
`ft_isalpha` · `ft_isdigit` · `ft_isalnum` · `ft_isascii` · `ft_isprint` · `ft_toupper` · `ft_tolower`

### `mem` — manipulation mémoire
`ft_memset` · `ft_bzero` · `ft_memcpy` · `ft_memmove` · `ft_memchr` · `ft_memcmp` · `ft_calloc`

### `string` — chaînes de caractères
`ft_strlen` · `ft_strlcpy` · `ft_strlcat` · `ft_strchr` · `ft_strrchr` · `ft_strncmp` · `ft_strnstr` · `ft_strdup` · `ft_substr` · `ft_strjoin` · `ft_split` · `ft_strtrim` · `ft_strmapi` · `ft_striteri` · `ft_atoi` · `ft_itoa`

### `put` — écriture sur descripteur
`ft_putchar_fd` · `ft_putstr_fd` · `ft_putendl_fd` · `ft_putnbr_fd`

### `list` — listes chaînées (`t_list`)
`ft_lstnew` · `ft_lstadd_front` · `ft_lstadd_back` · `ft_lstsize` · `ft_lstlast` · `ft_lstdelone` · `ft_lstclear` · `ft_lstiter` · `ft_lstmap`

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

### `gnl` — lecture ligne par ligne
`get_next_line` — lit un fd ligne par ligne, supporte plusieurs descripteurs en parallèle.

### `printf` — affichage formaté
`ft_printf` — conversions supportées : `%c %s %p %d %i %u %x %X %%`

---

## 🔍 Zoom : `get_next_line` multi-fd

Le reste de lecture de chaque fd est conservé dans un **tableau statique fixe**
(`char rest[FD_MAX][BUFFER_SIZE + 1]`) : aucun `malloc` pour le stash, et
plusieurs fd peuvent être lus en alternance sans se mélanger.

```mermaid
flowchart TD
    start(["get_next_line(fd)"]) --> chk{"fd valide ?<br/>0 ≤ fd < FD_MAX"}
    chk -- non --> retn["return NULL"]
    chk -- oui --> dup["buf = strdup(rest[fd])<br/>rest[fd] = \"\""]
    dup --> loop{"'\n' dans buf<br/>ou EOF ?"}
    loop -- non --> rd["read(fd, BUFFER_SIZE)<br/>buf = join(buf, temp)"]
    rd --> loop
    loop -- oui --> split["split au 1er '\n'"]
    split --> save["rest[fd] = reste après '\n'"]
    save --> line["return ligne (malloc)"]

    classDef n fill:#1e293b,stroke:#475569,color:#e2e8f0;
    classDef ok fill:#065f46,stroke:#10b981,color:#d1fae5;
    classDef ko fill:#7f1d1d,stroke:#ef4444,color:#fee2e2;
    class start,chk,dup,loop,rd,split,save n;
    class line ok;
    class retn ko;
```

**Lecture entrelacée de 3 fichiers :**

```mermaid
sequenceDiagram
    participant App
    participant GNL as get_next_line
    participant R as rest[FD_MAX]
    App->>GNL: get_next_line(fdA)
    GNL->>R: lit/écrit rest[fdA]
    GNL-->>App: "ligne A1"
    App->>GNL: get_next_line(fdB)
    GNL->>R: lit/écrit rest[fdB]
    GNL-->>App: "ligne B1"
    App->>GNL: get_next_line(fdA)
    GNL->>R: reprend rest[fdA]
    GNL-->>App: "ligne A2"
```

---

## 🖨 Zoom : `ft_printf`

```mermaid
flowchart LR
    in["chaîne format"] --> scan{"caractère ?"}
    scan -- "normal" --> w["write(1, c)"]
    scan -- "'%'" --> conv{"conversion"}
    conv -->|c| pc["ft_putchar"]
    conv -->|s| ps["ft_putstr"]
    conv -->|d / i| pn["ft_putnbr"]
    conv -->|u| pu["ft_putunbr"]
    conv -->|x / X| px["ft_puthex"]
    conv -->|p| pa["ft_putaddr"]
    conv -->|%| pp["'%'"]
    w --> cnt["+= compteur"]
    pc --> cnt
    ps --> cnt
    pn --> cnt
    pu --> cnt
    px --> cnt
    pa --> cnt
    pp --> cnt
    cnt --> ret["return total écrit"]

    classDef n fill:#1e293b,stroke:#475569,color:#e2e8f0;
    class in,scan,conv,w,pc,ps,pn,pu,px,pa,pp,cnt,ret n;
```

---

## ✅ Norme

Tout le code respecte la **norminette** (42). Vérification :

```bash
make norm
# ou
norminette srcs includes
```

---

<div align="center">
<sub>Fait avec ☕ et beaucoup de <code>-Wall -Wextra -Werror</code> — by <b>sgil--de</b></sub>
</div>
