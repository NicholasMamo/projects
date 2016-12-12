:- module(http, [refresh/0, arrive/3, belong/2, depart/3, flight/8, go/3, leave/3]).
:- use_module(library(http/http_open)).

% belong(Flight, Airline)
% arrive(Flight, Origin, Time)
% go(Flight, Destination, Time)
% leave(Flight, Origin, Time)

:- dynamic(arrive/3).
:- dynamic(belong/2).
:- dynamic(depart/3).
:- dynamic(flight/8).
:- dynamic(go/3).
:- dynamic(leave/3).

refresh() :- reset(),
				getOutboundFlights(),
				getInboundFlights(),
				reinterpret(),
				!.
				
reset() :- resetFlight(),
			resetArrival(),
			resetBelong(),
			resetDepart(),
			resetGo(),
			resetLeave().
			
resetFlight() :- (flight(Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status),
					retract(flight(Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status)),
					fail) ; true.
			
resetArrival() :- (arrive(Flight, Origin, Time),
					retract(arrive(Flight, Origin, Time)),
					fail) ; true.
					
resetBelong() :- (belong(Flight, Airline),
					retract(belong(Flight, Airline)),
					fail) ; true.
					
resetDepart() :- (depart(Flight, Origin, Time),
					retract(depart(Flight, Origin, Time)),
					fail) ; true.
					
resetGo() :- (go(Flight, Destination, Time),
				retract(go(Flight, Destination, Time)),
				fail) ; true.
					
resetLeave() :- (leave(Flight, Origin, Time),
					retract(leave(Flight, Origin, Time)),
					fail) ; true.
			
getOutboundFlights() :- load_html("http://rootyweb.com/departures.htm", HTML, []),
						parse_html(HTML, outbound).
						
getInboundFlights() :- load_html("http://rootyweb.com/arrivals.htm", HTML, []),
						parse_html(HTML, inbound).
				
parse_html([element(div, Attributes, Content)|Rest], Type) :- 
												checkAttributes(Attributes),
												!,
												getFlight(Content, List),
												addFlight(List, Type),
												parse_html(Rest, Type).
parse_html([element(_, _, Content)|Rest], Type) :- !, 
												parse_html(Content, Type),
												parse_html(Rest, Type).
parse_html([_|Rest], Type) :- parse_html(Rest, Type).
parse_html([], _).

checkAttributes([]) :- fail.
checkAttributes([class='arrivals-even'|_]) :- !.
checkAttributes([class='arrivals-odd'|_]) :- !.
checkAttributes([_|R]) :- checkAttributes(R).

getFlight(Raw, List) :- fetchContent(Raw, List).

fetchContent([], []).
fetchContent([element(_, _, [Content])|Remaining], [Content|Rest]) :- !, fetchContent(Remaining, Rest).
fetchContent([_|Remaining], Rest) :- fetchContent(Remaining, Rest).

addFlight([Airline, Destination, Flight, Craft, Time, Estimated], outbound) :- addFlight([Airline, Destination, Flight, Craft, Time, Estimated, ''], outbound).
addFlight([Airline, Destination, Flight, Craft, Time, Estimated, Status], outbound) :- preprocessFlight([Airline, Destination, Flight, Craft, Time, Estimated, Status], [PAirline, PDestination, PFlight, PCraft, PLeaves, PEstimated, PStatus]),
																					assert(flight(PAirline, 'MALTA', PDestination, PFlight, PCraft, PLeaves, PEstimated, PStatus)).

addFlight([Airline, From, Flight, Craft, Time, Estimated], inbound) :- addFlight([Airline, From, Flight, Craft, Time, Estimated, ''], inbound).
addFlight([Airline, From, Flight, Craft, Time, Estimated, Status], inbound) :- preprocessFlight([Airline, From, Flight, Craft, Time, Estimated, Status], [PAirline, PFrom, PFlight, PCraft, PLeaves, PEstimated, PStatus]),
																					assert(flight(PAirline, PFrom, 'MALTA', PFlight, PCraft, PLeaves, PEstimated, PStatus)).

add([]).
add([[Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status]|Rest]) :- assertz(belong(Flight, Airline)),
																						assertz(depart(Flight, Origin, Time)),
																						assertz(depart(Airline, Origin, Time)),
																						assertz(go(Flight, Destination, Time)),
																						assertz(go(Airline, Destination, Time)),
																						assertz(leave(Flight, Origin, Time)),
																						assertz(leave(Airline, Origin, Time)),
																						specifics(Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status),
																						add(Rest).

specifics(Airline, Origin, 'MALTA', Flight, Craft, Time, Estimated, Status) :- assertz(arrive(Flight, Origin, Time)),
																				assertz(arrive(Airline, Origin, Time)),
																				!.
specifics(_, _, _, _, _, _, _, _).

reinterpret() :- findall([Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status], flight(Airline, Origin, Destination, Flight, Craft, Time, Estimated, Status), L),
					add(L).

%preprocessFlight(A, A).					
preprocessFlight([], []).
preprocessFlight([H|T], [PH|PT]) :- preprocess(H, PSH),
									string(PSH),
									atom_codes(PH, PSH),
									!,
									preprocessFlight(T, PT).
preprocessFlight([H|T], [PH|PT]) :- preprocess(H, PH),
									preprocessFlight(T, PT).
					
preprocess(A, P) :- string_concat(H, ' ', A),
					!,
					preprocess(H, P).
preprocess(A, A).

read_file(In, Departures) :- open(In, read, Stream),
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
					
:- call(refresh()). % automatically call refresh upon compile-time
