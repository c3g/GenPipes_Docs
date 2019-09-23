:orphan:

.. _doc_gp_writing_guidelines:

GenPipes Writing Style Guide
=============================

How do we make it really easy and simple for GenPipes users to adopt GenPipes?

The very basic ingredient is GenPipesitself. It needs to be flexible, scalable, intuitive, easy to deploy and quick to gather information insights. Besides that, one of the key enablers towards facilitating GenPipes onboarding is its user documentation that satisfies the following criteria:

* Concise,
* Current & Continuously updated,
* Consistent,
* Clear, and
* Comprehensive 

This Writing Style guide is inspired by `Google Style Guide`_ which is adopted by several open source projects out there. Besides that, there are other references such as `API Documentation Guide`_, and `Best REST API Template`_. These are in use by many projects and many engineers, who collaborate globally to create world class software and documentation, used across verticals and industries.  As of writing this, GenPipes does not provide API interfaces yet.  It only provides executable that can be invoked to run various genomic pipelines.

.. doc_style_intro:

==================
Goals and Audience
==================

This guide is intended to help GenPipes technical writers to form a consistent approach for writing its documentation.

The primary goal of this guide is to codify and record decisions that Google's Developer Relations group makes about style. The guide can help you avoid making decisions about the same issue over and over, can provide editorial assistance on structuring and writing your documentation, and can help you keep your documentation consistent with our other documentation.

.. doc_how_to_use:

=====================
How to use this Guide
=====================

This guide is a reference document.  You can choose to read it linearly or look up specific issue or topic using the search box.

For issues not covered in this guide, see `Google Style Guide`_ or `Other Style Guides`_.

=============================
Restructured Text Style Guide
=============================
You may also want to refer to some of the 'coding' standards applied to documentation files developed using Sphinx automation engine and Restructured Text formal.  See `Sphinx Documentation Style Guide`_ for details.

.. doc_do_list:

----

===================
Documentation Do's
===================

+-------------------+---------------------------------------------------------------------------------+
|  Purpose          |               Guidelines                                                        |
+===================+=================================================================================+
|   Clarity         | Most of the principles that apply to good technical documentation also apply to |
|                   | accessible technical documentation:                                             |
|                   |                                                                                 |
|                   | * Use correct grammar and punctuation.                                          |
|                   | * Use active voice and present tense.                                           |
|                   | * Write clear, simple sentences.                                                |
|                   | * Be consistent.                                                                |
+-------------------+---------------------------------------------------------------------------------+
|   Comprehension   | Include screenshots!                                                            |
|                   | Users find screenshots very helpful, particularly annotated screenshots.        |
|                   | When using screenshots as figures, remember to circle the relevant buttons, add |
|                   | arrows pointing out mentioned links, or highlight key sections.                 |
+-------------------+---------------------------------------------------------------------------------+
|   Common norms    | Spell out numbers nine and under. Use numerals for 10 and up.                   |
+-------------------+---------------------------------------------------------------------------------+
|   Common norms    | Use comma before “and” in a list of several items.                              |
|                   | For example:                                                                    |
|                   | “This theme is elegant, simple, and easy to use.”                               |
+-------------------+---------------------------------------------------------------------------------+
|   Shared doc      | Do not delete, move or rename any document, page or topic which you do not own  |
|   development     | or did not create. Discuss and review as there may be cascading impact and      |
|   norm            | changes required to be done for the same. Collaborate on such wide impact       |
|                   | documentation changes.                                                          |
+-------------------+---------------------------------------------------------------------------------+
| Cross referencing | Be aware that the content of some pages is included in other pages. Make sure   |
| common norm       | you put your content in the right place, if it is cross referenced multiple     |
|                   | times and also across guides.  Follow similar principles just as in source code |
|                   | common files and function norms. This applies in particular to the Concepts and |
|                   | Usage Guide, FAQ, SDK API documentation.                                        |
+-------------------+---------------------------------------------------------------------------------+
|  Document         | If you are inserting a topic in an already existing piece of content, say a page|
|  Consistency      | or in a new section, ensure that you follow a consistent style, layout, grammar | 
|                   | and format with the rest of the page.                                           |
+-------------------+---------------------------------------------------------------------------------+

----

======================
Documentation Do not's
======================

+-------------------+---------------------------------------------------------------------------------+
|  Purpose          |               Guidelines                                                        |
+===================+=================================================================================+
|   No Cryptic      | Avoid the use of Buzzwords. When you use any acronym, expand it for first time  |
|    words          | use, with acronym in brackets. For subsequent use, acronym is fine.             | 
|                   |                                                                                 |
|                   | | **Not recommended**: Use JBMgmtSvc to schedule this task if this policy is    |
|                   | | breached.                                                                     |
|                   | |                                                                               |
|                   | | **Recommeded**: Use Job Management Service (JBMgmtSvc) to schedule this task  |
|                   | | if privacy policy is breached. Refer to JBMgmtSvc details here (refer to link)|
|                   | | on how to set up job management schedule                                      |
|                   | |                                                                               |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|   No Complicated  | No long sentences. Think of the twitter 140 characters generation. Avoid choppy |
|   Language        | sentences.                                                                      |
|                   |                                                                                 |
|                   | .. tip:: Think of your audience                                                 |
|                   |                                                                                 |
|                   |    Compare the first paragraph below to the second in terms of complexity.      |
|                   |      - When you write, imagine you speaking these very same words as if you were|
|                   |        saying these to someone in a conference call or Webinar where no real    |
|                   |        real time clarification or feedback is possible by those who'd read it   |
|                   |        and try to understand what you wrote at a later point in time.           |
|                   |      - When you write, imagine your audience reading what you write, at a later |
|                   |        point in time. Face to face conversation allow the luxury of real-time   |
|                   |        clarifications, additional cues via facial expressions and tone. Written |
|                   |        word is more powerful and could be confusing as it lacks that luxury.    |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|  Avoid Repetition | Use of repetitive phrases such as 'To do', or 'Here is', or "You can" at the    |
|                   | start of each sentence is detrimental to reader attention.                      |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|  Enterprise       | Avoid current pop-culture references.                                           |
|  Focus            |                                                                                 |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|  Appropriate      | No Jokes at the expense of customers, competitors or anyone else for that       |
|  Language         | matter.                                                                         | 
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|  Spoiler Alert    | Avoid trying to document or talk about future features or solutions or products |
|                   | or enhancements, even in innocuous ways.                                        |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+
|  Ambiguity        | Avoid the modal verbs such as could, may, might, and should in technical        |
|                   | documentation. Modal verbs are ambiguous and leave the reader wondering what to |
|                   | do. For details, visit `Modal Style Guide`_.                                    |
|                   |                                                                                 |
+-------------------+---------------------------------------------------------------------------------+

.. The following are hyperlink references and this is a comment that should not show up in actual techdocs

.. _Modal Style Guide: https://developer.salesforce.com/docs/atlas.en-us.salesforce_pubs_style_guide.meta/salesforce_pubs_style_guide/style_can.htm

.. _Google Style Guide: https://developers.google.com/style/

.. _API Documentation Guide: https://www.mulesoft.com/resources/api/guidelines-api-documentation

.. _Best REST API Template: https://blog.readme.io/the-best-rest-api-template/

.. _Other Style Guides: https://developers.google.com/style/resources

.. _Sphinx Documentation Style Guide: http://documentation-style-guide-sphinx.readthedocs.io/en/latest/style-guide.html
