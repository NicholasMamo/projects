% grammar
s --> np, !. % for now, a sentence is only made up of a noun phrase
np --> sd, !, ap, sn.
np --> pd, !, ap, pn.
np --> ap, sn.
np --> ap, pn.
ap --> a, !, ap.
ap --> [].

% lexicon
sd --> [a].
sd --> [the].
pd --> [the].
a --> [brown].
a --> [white].
a --> [small].
a --> [big].
sn --> [dog].
sn --> [cat].
pn --> [dogs].
pn --> [cats].
