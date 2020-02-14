# Repartition des fonctions de teste a coder

## implémentation
> Victor ANDRAULT
- truc

> Arthur BLONDEAU
- truc

> Charles GOEDEFROIT
- test
```
def ToutesSequencesBinairesRecT(n):
    def aux(v, acc):
      if v < 0:
        return acc
      return aux(v-1, acc + (EntierVersBinaire(n, v),))
    return aux(2**n-1, ())
```

## Tests
> Victor ANDRAULT
- truc

> Arthur BLONDEAU
- truc

> Charles GOEDEFROIT
- truc


## todo :
- solver bruteforce
- solver complet