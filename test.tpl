<?cs each:op = Op ?>
(define (<?cs name:op ?><?cs each:in = op.input_arg ?> <?cs name:in ?><?cs /each ?>)
  (tf-<?cs name:op ?>
    graph
    (gensym "x")
    <?cs each:in = op.input_arg ?> <?cs name:in ?><?cs /each ?>))
<?cs /each ?>
