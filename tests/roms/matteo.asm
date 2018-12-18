section "code", rom0

ld b, 6
ld h, b

ld c, 7
ld h, c

ld d, 8
ld h, d

ld e, 9
ld h, e

ld h, 10
ld h, h

ld l, 11
ld h, l

ld [hl], 12
ld h, [hl]

ld a, 5
ld h, a

ld l, b

ld l, c

ld l, d

ld l, e

ld h, 5
ld l, h

ld l, l

ld l, [hl]

ld l, a

halt