#lang racket

;; Essentially want to boot up, retreive data from config
;; file, display window managers, get selection from user
;; then append the command to .xinitrc and run `startx`

;; Window Manager Data
(struct window-man (name exec))

;; Functionality
; Map Name Window-Man -> IO
(define (show-wms wms)
  (define (show-wm wm-name)
    (display (string-append wm-name "\n")))
  (let* ([keys (hash-keys wms)]
         [ixs  (for/list ([i (length keys)]) (number->string (+ 1 i)))])
    (display "Select a window manager:\n")
    (map (λ (ix name) (display (string-append " " ix ". " name "\n")))
         ixs
         keys)
    (display "\n")))

; Input-Source -> Map Nme Window-Man -> Window-Man
(define (select-dialog input-reader wm-map)
  (show-wms wm-map)
  (define input (input-reader))
  (if (hash-has-key? wm-map input)
      (hash-ref wm-map input)
      (select-dialog input-reader wm-map)))

; Window-Man -> IO
(define (run-wm wm)
  (display
   (string-append
    (string-append "Running " (window-man-name wm) "...\n")
    (string-append "Command: " (window-man-exec wm) "\n"))))

;; Program
(define (simdim config-reader input-reader config-src)
  (let* ([wms (config-reader config-src)]
         [selection (select-dialog input-reader wms)])
    (run-wm selection)))

;; Actual providers
(define (terminal-input)
  (display "Enter choice: ")
  (read-line (current-input-port) 'any))

;; Test rigging
(define (dummy-config-reader filename)
  (make-hash `(("xmonad" . ,(window-man "xmonad" "xmonad-exec-cmd"))
               ("plasma" . ,(window-man "plasma" "start-plasma")))))

(define (dummy-input-reader) "xmonad")

;; Entry
(define (display-banner)
  (display "\n")
  (display "+--------+\n")
  (display "| SIMDIM : The simple display manager\n")
  (display "+--------+\n"))

(module* main #f
  (display-banner)
  (simdim dummy-config-reader terminal-input "blah"))
