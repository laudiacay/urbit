::  %sprk, just a prng
!:
!?  164
::
|=  our=ship
=>  |% :: move is abstraction over all event types that you can send
:: note is a request that you send to another vane (theyll get it as a task)
:: a sign is a response that you get from another vane (the vane will produce it as a gift)

    +$  move  [p=duct q=(wite _!! gift:sprk)]
    ::
    +$  sprk-state
      $:  %0
          entropy-pool=@
          counter=@ud
          driver=duct
      ==
    --
::
=|  sprk-state
=*  state  -
|=  [now=@da eny=@uvJ rof=roof]
=*  sprk-gate  .
^?
|%
::  +call: handle a +task:sprk request
::
++  call
  |=  $:  hen=duct :: cargo cult it for now, its about how arvo dispatches events
          dud=(unit goof) :: signal that we are handling an error
          wrapped-task=(hobo task:sprk) :: dumb little type hack??? if the event came from the runtime, it's untyped, if it came from a vane, it's typed
      ==
  ^-  [(list move) _sprk-gate]
  ::
  =/  =task:sprk  ((harden task:sprk) wrapped-task) :: this tries to "harden" -> if its typed, nothing, if its untyped, you mold it into a "task" from lull. then assign that to variable task in subject- shadowing :)
  ::=|  =task:sprk
  ::
  =^  moves  state :: this line is the "state monad" in that moves is "new/"pinned"
    :: state is replaced

    ::
    ::  handle error notifications
    ::
    ?^  dud  !!
    ::
    ?-  -.task :: CR: this is where the tasks are lists where it tells u what to do w the data
      %born  [~ state(driver hen)] :: cig is the empty list, and second thigng is we change state so that driver->=hen
      %trim  [~ state]
      %vega  [~ state] :: these are noops- you can also say `state to nullprefix cell of state
      %hmor  !!
      %rreq  !!
      ::%hmor  [~ state(entropy-pool (pool-add entropy-pool p.task))] :: this is the entropy from the thing!! eventually there will be moves here (replying to blocking requests for entropy)
      ::%rreq  [(sending entropy back to the guy) (updating the state to the next iteration of entropy generation woooooo)] :: you have to implement this
    ==
  [moves sprk-gate] :: CR: you are producing a list of moves and an outer copy of the behn-gate
  :: CR: in this case the moves will be sending entropy back out
  :: CR: 
::  +load: migrate an old state to a new behn version
::   a state migration: get a new version of a vane! its gotta adapt the state of the old vane, this is like an OTA- just takes the old vane's state in.
++  load
  |=  old=sprk-state
  ^+  sprk-gate
  sprk-gate(state old)
::  +scry: view state (namespace handler) (this is not what i wanna do lol)
::
::    TODO: not referentially transparent w.r.t. elapsed timers,
::    which might or might not show up in the product
::    pure, referentially transparent read from the vane, as specified from those arguments
++  scry
  ^-  roon
  |=  [lyc=gang car=term bem=beam]
  ^-  (unit (unit cage))
  ~
::
++  stay  state :: give me ur state!! call stay on the old vane, pass to load on the new vane
++  take   !!  :: call is a request that gives you a task, this is "taking" a gift, which is when another vane sends you a gift and you get a sign (which is a gift plus the name of the guy who sent it)
:: this is when you send a thing to another vane and then they send something back
--
