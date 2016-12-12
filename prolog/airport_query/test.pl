read_departures(Departures) :- open('passengers.maltairport.com_en_arrivals.htm', read, Stream),
						buildFromStream(Stream, Temp),
						truncate(Temp, Truncated),
						atomic_list_concat(Truncated, '', Atom),
						atom_string(Atom, Departures).
						
buildFromStream(Stream, [H|Rest]) :- get_code(Stream, C),
										not(eof(C)),
										!,
										checkChar(C, H),
										buildFromStream(Stream, Rest).
										
buildFromStream(Stream, "") :- get_code(Stream, C),
								eof(C).
										
buildFromStream(_, _).

checkChar(10, '') :- !. 

checkChar(32, '') :-  !. 

checkChar(-1, '') :-  !. 

checkChar(end_of_file, '') :-  !.

checkChar(A, W) :- atom_codes(W, [A]).

eof(-1).

truncate([_], []) :- !.
truncate([H|T], [H|Rest]) :- truncate(T, Rest).

preprocess(A, P) :- string_concat(H, ' ', A),
					!,
					preprocess(H, P).
preprocess(A, A).
