ABOUT
=====
 * This is a Git mirror of [Svn trunk of Kaldi project](http://sourceforge.net/projects/kaldi/)
   `svn://svn.code.sf.net/p/kaldi/code/trunk`
 * In the branch `master` I commit my work. In the branch `svn_mirror` I mirror `svn://svn.code.sf.net/p/kaldi/code/trunk`. In the branch `sandbox_oplatek` I am developing changes which I would like to check in back to Kaldi.
 * Currently, I mirror the repository manually as often as I needed.
 * The main purpose for mirroring is that I want to build my own decoder and train my models for decoding based on up-to-date Kaldi version.
 * Recipe for training the models can be found at `egs/kaldi-vystadial-recipe`
 * Source code for python wrapper for online-decoder is at `src/python-kaldi-decoding` 
 * Remarks about new decoder are located at `src/vystadial-decoder`
 * I use the `Fake submodules` approach to merge the 3 subprojects to this repository. More about `Fake submodules` [at this blog](http://debuggable.com/posts/git-fake-submodules:4b563ee4-f3cc-4061-967e-0e48cbdd56cb).
 * I mirror the svn via `git svn`. [Nice intro to git svn](http://viget.com/extend/effectively-using-git-with-subversion) and [Walk through](http://blog.shinetech.com/2009/02/17/my-git-svn-workflow/)

OTHER INFO
----------
 * Read `INSTALL.md` and `INSTALL` first!
 * For training models read `egs/kaldi-vystadial-recipe/s5/README.md`
 * For building and developing decoder callable from python read `src/python-kaldi-decoding/README.md`
 * For information about new decoder read `src/vystadial-decoder/README.md`
 * This work is done under [Vystadial project](https://sites.google.com/site/filipjurcicek/projects/vystadial).

LICENSE
--------
 * One of our goals is to release all of the added features under `Apache license 2.0` (Kaldi uses the same license). However, we did not added any license statement to repository yet. If you see this README and do not know the licensing conditions, write us. We probably just forget to put the license under the repository.
 * We also want to publicly release the training data in the autumn 2013.
