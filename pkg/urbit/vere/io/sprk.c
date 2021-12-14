/* vere/sprk.c
**
*/
#include "all.h"
#include "vere/vere.h"

// need help with: 
// 1. error convention
// 2. naming
// 3. making sure this is correct in general
// 4. making sure i'm not leaking memory?
// 5. how do i print things out in here to make sure my pointer math is right?... i feel okay about it but not perfect.

/* u3_sprk: randomness vane's io driver.
   name comes from https://copypastatext.com/penguin-of-doom/ and is pronounced spork. it is very random, indeed.
*/
  typedef struct _u3_sprk {
    u3_auto    car_u;                   //  driver
  } u3_sprk;

/* _sprk_bail_dire(): c3y if fatal error. RETAIN
*/
static c3_o
_sprk_bail_dire(u3_noun lud)
{
  u3_noun mot = u3r_at(4, lud);

  if (  (c3__meme == mot)
     || (c3__intr == mot) )
  {
    return c3n;
  }

  return c3y;
}

/* _sprk_wake_bail(): %wake is essential, retry failures.
*/
static void
_sprk_wake_bail(u3_ovum* egg_u, u3_noun lud)
{
  u3_auto* car_u = egg_u->car_u;

  if (  (2 > egg_u->try_w)
     && (c3n == _sprk_bail_dire(lud)) )
  {
    u3z(lud);
    u3_auto_redo(car_u, egg_u);
  }
  else {
    u3_auto_bail_slog(egg_u, lud);
    u3_ovum_free(egg_u);

    u3l_log("sprk: randomness vane failed; queue blocked\n");

    //  XX review, add flag to continue?
    //
    u3_pier_bail(car_u->pir_u);
  }
}

/* _sprk_born_news(): initialization complete on %born.
*/
static void
_sprk_born_news(u3_ovum* egg_u, u3_ovum_news new_e)
{
  u3_auto* car_u = egg_u->car_u;

  if ( u3_ovum_done == new_e ) {
    car_u->liv_o = c3y;
  }
}

/* _sprk_born_bail(): %born is essential, retry failures.
*/
// need to be able to send a born event and also a retry- vane needs a wire to the driver, every single time
// the born event, on the vane side, will initialize some nice checks to refresh entropy pools and the like :)
static void
_sprk_born_bail(u3_ovum* egg_u, u3_noun lud)
{
  u3_auto* car_u = egg_u->car_u;

  if (  (2 > egg_u->try_w)
     && (c3n == _sprk_bail_dire(lud)) )
  {
    u3z(lud);
    u3_auto_redo(car_u, egg_u);
  }
  else {
    u3_auto_bail_slog(egg_u, lud);
    u3_ovum_free(egg_u);

    u3l_log("sprk: initialization failed\n");

    //  XX review, add flag to continue?
    //
    u3_pier_bail(car_u->pir_u);
  }
}
/* _sprk_io_talk(): notify %sprk that we're live
*/
static void
_sprk_io_talk(u3_auto* car_u)
{
  // wire looks like /sprk/
  u3_noun wir = u3nc(c3__sprk, u3_nul);
  u3_noun cad = u3nc(c3__born, u3_nul);

  u3_auto_peer(
    u3_auto_plan(car_u, u3_ovum_init(0, c3__s, wir, cad)),
    0,
    _sprk_born_news,
    _sprk_born_bail);
}

/* _sprk_ent_send(): get the requested entropy and send it into sprk vane
  can fail if libent fails
  rounds up to nearest 512-bit/64-byte amount of entropy
*/
static void
_sprk_ent_send(u3_auto* car_u, u3_noun byt) {

  if (c3n == u3a_is_atom(byt)) goto exit;
  c3_w n_bytes = u3r_word(0, byt);

  // make sure it's not too much entropy and round it up to a multiple of c3_rand size
  if (n_bytes > 1024) goto exit;
  if (n_bytes % 64 > 0) {
    n_bytes += 64 - (n_bytes % 64);
  }

  // allocate a buffer
  c3_w* bytbuf = c3_malloc(n_bytes);

  // fill the buffer piece by piece - this pointer math needs a check!
  int calls = n_bytes / 64;
  for (int i=0 ; i < calls; i++) {
    c3_rand(&bytbuf[16*i]);
  }

  // turn it into a noun and free it
  u3_noun entr = u3i_words(n_bytes, bytbuf);
  free(bytbuf);

  u3_noun wir = u3nc(c3__sprk, u3_nul);
  
  // card looks like: c3__hmor, number of bytes, entropy stream bytes, u3_nul
  u3_noun cad = u3nt(c3__hmor, u3i_word(n_bytes), entr);
  // send the entropy in
  u3_auto_plan(car_u, u3_ovum_init(0, c3__s, wir, cad));
  
  // and decrement reference count
  exit: u3z(byt);

  // done :)
}


/* _sprk_io_kick(): apply effects.
*/
static c3_o
_sprk_io_kick(u3_auto* car_u, u3_noun wir, u3_noun cad)
{
  u3_noun tag, dat, i_wir;
  c3_o ret_o;

  if (  (c3n == u3r_cell(wir, &i_wir, 0))
     || (c3n == u3r_cell(cad, &tag, &dat))
     || (c3__sprk != i_wir) 
     || (c3__hreq != tag))
  {
    ret_o = c3n;
  }
  else {
    ret_o = c3y;
    _sprk_ent_send(car_u, u3k(dat));
  }

  u3z(wir); u3z(cad); // these are refcounting! decrements the refcounts :)
  return ret_o;
}


/* _sprk_io_exit(): free the memory we allocated... DONE?
*/
static void
_sprk_io_exit(u3_auto* car_u)
{
  u3_sprk* teh_u = (u3_sprk*)car_u;
  c3_free(teh_u);
}

/* u3_sprk(): initialize randomness vane driver... DONE?
*/
u3_auto*
u3_sprk_io_init(u3_pier* pir_u)
{
  u3_sprk* teh_u = c3_calloc(sizeof(*teh_u));

  u3_auto* car_u = &teh_u->car_u;
  car_u->nam_m = c3__sprk;

  car_u->liv_o = c3n;
  car_u->io.talk_f = _sprk_io_talk;
  car_u->io.kick_f = _sprk_io_kick;
  car_u->io.exit_f = _sprk_io_exit;

  return car_u;
}
