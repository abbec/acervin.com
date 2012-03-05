---
title: Adventures in the HTML5 history API
kind: article
created_at: 2011-09-08 19:20
tags: ['web']
---

When developing drinkmixen we decided that we needed to have a
javascript slider for pagination (like the
[GitHub tree slider](https://github.com/blog/760-the-tree-slider "GitHub Tree slider")).

The difference is that our slider is used in pagination.

<p>
<img src="/blog/2011/sep/img/pages.png" alt="Pages" />
</p>

To accomplish this we had to look into the [HTML5 history API](http://www.w3.org/TR/html5/history.html). This is
not a HTML API per se but a JavaScript interface. The main idea is
that the click on a page link, next or previous button is
intercepted. The JavaScript method `pushState()` is then used to
actually push a state to the browsers history stack.

The main idea looks like this (with jQuery):

    #!javascript
    $(".page-nav").click(function(){
        history.pushState({location: this.href}, "page", this.href);
        $("#center").replaceWithGet(this.href, current_url);
    });

So, a new state is pushed to the browser history stack and then the
new page is loaded with an Ajax GET call and the slide is done with a
custom jQuery animation. Now the url is updated when
the user clicks on a page link and all is fine.

The next problem arises when the user clicks his/her back button in
the browser. Then we need a `popState` handler to handle this event.
What we basically do in the `popState` handler is just load and
display the appropriate page with a nice animation.

It is not all that easy though... It works fine in some browsers but
not at all in others. This is since different browsers have different
opinions on when a `popState` event is to be fired. For a nice
crossbrowser solution (except for Internet Explorer of course that
does not at all support the history API) I would suggest looking at
[pjax](http://pjax.heroku.com/).

To have real cross-browser support for the history API there is always
[History.js](http://plugins.jquery.com/project/history-js) but since we
did not want to include more external JavaScript libraries we decided
that Internet Explorer users will have a less pleasing visual
experience.

P.S. I often use IE myself :) D.S.
